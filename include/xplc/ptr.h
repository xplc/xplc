/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef __XPLC_PTR_H__
#define __XPLC_PTR_H__

/** \file
 *
 * Smart pointer for XPLC interfaces.
 */

#include <assert.h>
#include <xplc/IObject.h>

#ifndef UNSTABLE
#error "xplc_ptr is experimental!"
#endif

/**
 * Shim class for xplc_ptr.  This is so we can tag a pointer so that
 * we can use a specific xplc_ptr constructor.
 */
class already_addrefed {
public:
  /** Pointer that is tagged. */
  IObject* ptr;
  /** Automatically invoked constructor. You never need to explicitly
   *  use this class, it will get involved automatically by the C++
   *  compiler when necessary. */
  already_addrefed(IObject* obj): ptr(obj) {}
};

/**
 * Indicates to xplc_ptr that a pointer does not need to be
 * addRef()'d.
 */
template<class T> already_addrefed dont_addref(T* obj) {
  return already_addrefed(obj);
}


/**
 * Shim class for xplc_ptr.  This is so we can tag a pointer so that
 * we can use a specific xplc_ptr constructor.
 */
class want_to_keep {
public:
  /** Pointer that is tagged. */
  IObject* ptr;
  /** Automatically invoked constructor. You never need to explicitly
   *  use this class, it will get involved automatically by the C++
   *  compiler when necessary. */
  want_to_keep(IObject* obj): ptr(obj) {}
};


/**
 * Indicates to xplc_ptr that a pointer should not be release()'d.
 */
template<class T> want_to_keep dont_release(T* obj) {
  return want_to_keep(obj);
}


/**
 * Smart pointer class for XPLC interfaces.
 */
template<class T> class xplc_ptr {
private:
  T* ptr;

  class Protected: public T {
  private:
    virtual unsigned int addRef() = 0;
    virtual unsigned int release() = 0;
  };

  void set(IObject* obj) {
    if(ptr)
      ptr->release();

    if(!obj) {
      ptr = 0;
      return;
    }

    ptr = static_cast<T*>(obj->getInterface(XPLC_IID<T>::get()));
  }

  T**& operator&();

public:
  xplc_ptr(): ptr(0) {}

  /**
   * Copy constructor.
   */
  xplc_ptr(const xplc_ptr<T>& obj) {
    set(obj.ptr);
  }

  /**
   * Constructs an xplc_ptr from an IObject pointer. The ownership is
   * transferred to the xplc_ptr. In other word, the pointer passed as
   * parameter to this constructor is then invalid.
   *
   * Use dont_release() if you want the ownership to be shared.
   */
  xplc_ptr(IObject* obj): ptr(0) {
    set(obj);
    if(obj)
      obj->release();
  }

  /**
   * Constructs an xplc_ptr from an IObject pointer that has already
   * been addRef()'d for you.
   */
  xplc_ptr(already_addrefed obj): ptr(0) {
    set(obj.ptr);
    if(obj.ptr)
      obj.ptr->release();
  }

  /**
   * Constructs an xplc_ptr from an IObject pointer without
   * invalidating the pointer. You still have to call
   * IObject::release() on that pointer for the object to be properly
   * destroyed.
   */
  xplc_ptr(want_to_keep obj): ptr(0) {
    set(obj.ptr);
  }

  ~xplc_ptr() {
    if(ptr)
      ptr->release();
  }

  /**
   * Replaces the current value of the xplc_ptr with the specified
   * IObject pointer. The ownership is transferred to the xplc_ptr
   * (the pointer is invalid after this operation).
   */
  xplc_ptr<T>& operator=(IObject* obj) {
    set(obj);
    if(obj)
      obj->release();
    return *this;
  }

  /**
   * Replaces the current value of the xplc_ptr with the specified
   * IObject pointer. The ownership is transferred to the xplc_ptr
   * (the pointer is invalid after this operation).
   */
  xplc_ptr<T>& operator=(already_addrefed obj) {
    set(obj.ptr);
    if(obj.ptr)
      obj.ptr->release();
    return *this;
  }

  /**
   * Replaces the current value of the xplc_ptr with the specified
   * IObject pointer. This is a simple copy, the pointer is still
   * valid after this operation.
   */
  xplc_ptr<T>& operator=(want_to_keep obj) {
    set(obj.ptr);
    return *this;
  }

  /**
   * Operator used to invoke methods on the object pointed at by the
   * xplc_ptr.
   */
  Protected* operator->() {
    assert(ptr);
    return static_cast<Protected*>(ptr);
  }

  /**
   * Obtain the raw pointer from the xplc_ptr. It will be addRef()'d.
   */
  T* getRaw() {
    if(ptr)
      ptr->addRef();

    return ptr;
  }

  /**
   * Internal use operator. Is used for interaction between multiple
   * xplc_ptr.
   */
  operator want_to_keep() {
    return want_to_keep(ptr);
  }

  /**
   * Tests whether the xplc_ptr is pointing at an object or not.
   */
  operator bool() {
    return ptr != 0;
  }
};


#endif /* __XPLC_PTR_H__ */
