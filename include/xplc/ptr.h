/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002-2004, Pierre Phaneuf
 * Copyright (C) 2002-2004, Net Integration Technologies, Inc.
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
 *
 * As a special exception, you may use this file as part of a free
 * software library without restriction.  Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU Lesser General Public
 * License.  This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Lesser
 * General Public License.
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
 * Smart pointer class for XPLC interfaces.
 */
template<class T>
class xplc_ptr {
private:
  T* ptr;

  class ProtectedPtr: public T {
  private:
    virtual unsigned int addRef() = 0;
    virtual unsigned int release() = 0;
#ifndef __XPLC_DELETE_H__
    void operator delete(void*);
#endif
  };

  xplc_ptr& operator=(const xplc_ptr&);

public:
  xplc_ptr():
    ptr(0) {
  }
  explicit xplc_ptr(T* aObj):
    ptr(aObj) {
  }
  template<class P>
  explicit xplc_ptr(const xplc_ptr<P>& aObj):
    ptr(aObj) {
    if(ptr)
      ptr->addRef();
  }
  ~xplc_ptr() {
    if(ptr)
      ptr->release();
  }
  ProtectedPtr* operator->() const {
    return static_cast<ProtectedPtr*>(ptr);
  }
  operator ProtectedPtr*() const {
    return static_cast<ProtectedPtr*>(ptr);
  }
  xplc_ptr& operator=(T* _ptr) {
    if(_ptr)
      _ptr->addRef();

    if(ptr)
      ptr->release();

    ptr = _ptr;

    return *this;
  }
};

#endif /* __XPLC_PTR_H__ */
