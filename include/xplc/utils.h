/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#ifndef __XPLC_UTILS_H__
#define __XPLC_UTILS_H__

/** \file
 *
 * Various utility functions, macros and templates.
 */

#include <stddef.h>
#include <xplc/IWeakRef.h>
#include <xplc/IFactory.h>

/**
 * Utility structure used for the interface map.
 */
struct UUID_Info {
  //@{
  const UUID* iid;
  ptrdiff_t delta;
  //@}
};

/**
 * Start the interface map for "component".
 */
#define UUID_MAP_BEGIN(component) const UUID_Info GenericComponent<component>::uuids[] = {

/**
 * Add an entry to an interface map.
 */
#define UUID_MAP_ENTRY(iface) { &iface##_IID, reinterpret_cast<ptrdiff_t>(static_cast<iface*>(reinterpret_cast<ThisComponent*>(1))) - 1 },

/**
 * Add an entry to an interface map for an ambiguous interface. The
 * second parameter is the interface that should be used to
 * disambiguate.
 */
#define UUID_MAP_ENTRY_2(iface, iface2) { &iface##_IID, reinterpret_cast<ptrdiff_t>(static_cast<iface2*>(reinterpret_cast<ThisComponent*>(1))) - 1 },

/**
 * Marks the end of an interface map.
 */
#define UUID_MAP_END { 0, 0 } };

/** \class WeakRef
 *
 * Common implementation of a weak reference.
 */
class WeakRef: public IWeakRef {
public:
  /** The object that the weak reference is pointing at. */
  IObject* object;
  virtual IObject* getObject() {
    if(object)
      object->addRef();

    return object;
  }
};

/** \class GenericComponent
 *
 * Mix-in template that contains an implementation of methods a basic
 * component will need to implement.
 */
template<class Component>
class GenericComponent: public Component {
private:
  typedef GenericComponent ThisComponent;
  static const UUID_Info uuids[];
  unsigned int refcount;
  WeakRef* weakref;
public:
  /** Provides a static function that can be passed to
   *  IGenericFactory::setFactory(). */
  static IObject* create() {
    return new GenericComponent;
  }
  GenericComponent(): refcount(0), weakref(0) {
  }
  /** Implements IObject::addRef(). */
  virtual unsigned int addRef() {
    return ++refcount;
  }
  /** Implements IObject::release(). */
  virtual unsigned int release() {
    if(--refcount)
      return refcount;

    /* protect against re-entering the destructor */
    refcount = 1;

    if(weakref)
      weakref->object = 0;

    delete this;

    return 0;
  }
  /** Implements IObject::getInterface(). */
  virtual IObject* getInterface(const UUID& uuid) {
    return XPLC_getInterface_real(this, uuid, uuids);
  }
  /** Implements IObject::getWeakRef(). */
  virtual IWeakRef* getWeakRef() {
    if(!weakref) {
      weakref = new GenericComponent<WeakRef>;
      weakref->addRef();
      weakref->object = this->getInterface(IObject_IID);
      this->release();
    }

    return weakref;
  }
};

/**
 * Internal function used by GenericComponent to implement
 * IObject::getInterface().
 */
IObject* XPLC_getInterface_real(void* self, const UUID& uuid,
                                const UUID_Info* uuidlist);

/**
 * %XPLC equivalent to dynamic_cast.  This templated function is a
 * typesafe way to call the getInterface method of a component and
 * cast it properly.  If the component does not support the interface,
 * a NULL pointer will be returned.
 */
template<class Interface>
Interface* get(IObject* aObj) {
  if(!aObj)
    return 0;

  return static_cast<Interface*>(aObj->getInterface(IID<Interface>::get()));
}

/**
 * A version of get() that releases its parameter.  This templated
 * function is very similar to the "get" one, except that it
 * automatically releases the inbound reference, without regard
 * whether the getInterface actually yielded something.
 */
template<class Interface>
Interface* mutate(IObject* aObj) {
  Interface* rv;

  if(!aObj)
    return 0;

  rv = static_cast<Interface*>(aObj->getInterface(IID<Interface>::get()));

  aObj->release();

  return rv;
}

/**
 * Shorthand to get a factory, create an object and get an interface.
 */
template<class Interface>
Interface* create(const UUID& cid) {
  IServiceManager* servmgr;
  IFactory* factory;
  Interface* rv;

  servmgr = XPLC_getServiceManager();
  if(!servmgr)
    return 0;

  factory = mutate<IFactory>(servmgr->getObject(cid));
  servmgr->release();
  if(!factory)
    return 0;

  rv = mutate<Interface>(factory->createObject());

  factory->release();

  return rv;
}

#endif /* __XPLC_UTILS_H__ */
