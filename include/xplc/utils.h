/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef __XPLC_UTILS_H__
#define __XPLC_UTILS_H__

#include <xplc/IObject.h>

/*
 * Define this if you want to debug components using the
 * GenericComponent template.
 */
#undef GENERICDEBUG

/*
 * Define this if you want to debug addRef()s and release()s.
 */
#undef GENERICDEBUG_REFS

#if defined(GENERICDEBUG) || defined(GENERICDEBUG_REFS)
#include <stdio.h>
#endif

/*
 * This template contains an implementation of methods a basic
 * component will need to implement.
 */

template<class Component>
class GenericComponent: public Component {
private:
  unsigned int refcount;
public:
  GenericComponent(): refcount(0) {
#ifdef GENERICDEBUG
    fprintf(stderr, "%s: instantiated\n", __PRETTY_FUNCTION__);
#endif
  }
#ifdef GENERICDEBUG
  virtual ~GenericComponent() {
    fprintf(stderr, "%s: destroyed\n", __PRETTY_FUNCTION__);
  }
#endif
  void operator delete(void* self) {
    ::operator delete(self);
  }
  virtual unsigned int addRef() {
#ifdef GENERICDEBUG_REFS
    fprintf(stderr, "%s = %i\n", __PRETTY_FUNCTION__, refcount + 1);
#endif

    return ++refcount;
  }
  virtual unsigned int release() {
#ifdef GENERICDEBUG_REFS
    fprintf(stderr, "%s = %i\n", __PRETTY_FUNCTION__, refcount - 1);
#endif

    if(--refcount)
      return refcount;

    /* protect against re-entering the destructor */
    refcount = 1;

    delete this;

    return 0;
  }
};

/*
 * This templated function is a typesafe way to call the getInterface
 * method of a component and cast it properly. If the component does
 * not support the interface, a NULL pointer will be returned.
 */

template<class Interface>
Interface* getInterface(IObject* aObj) {
  if(!aObj)
    return NULL;

  return (Interface*)aObj->getInterface(Interface::IID);
}

/*
 * This templated function is very similar to the getInterface one,
 * except that it automatically releases the inbound reference,
 * without regard whether the getInterface actually yielded something.
 */

template<class Interface>
Interface* mutateInterface(IObject* aObj) {
  Interface* rv;

  if(!aObj)
    return NULL;

  rv = (Interface*)aObj->getInterface(Interface::IID);

  aObj->release();

  return rv;
}

#endif /* __XPLC_UTILS_H__ */
