/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2001-2002, Pierre Phaneuf
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

#include "test.h"
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "../xplc/statichandler.h"

/*
 * test005
 *
 * Verifies the generic component template.
 */

class IFoo: public IObject {
public:
  static const UUID IID;
  virtual unsigned int getFoo() = 0;
  virtual void setFoo(unsigned int) = 0;
};

const UUID IFoo::IID = {0xdacffda8, 0x5eb4, 0x4c9b, {0xb5, 0xd4, 0x6d, 0xc5, 0x95, 0x5e, 0x4f, 0x74}};

class IBar: public IObject {
public:
  static const UUID IID;
  virtual unsigned int getBar() = 0;
  virtual void setBar(unsigned int) = 0;
};

const UUID IBar::IID = {0xa1520c1d, 0xcf44, 0x4830, {0xa9, 0xb2, 0xb1, 0x80, 0x9b, 0x1e, 0xe7, 0xa2}};

class MyTestObject: public IFoo, IBar {
private:
  bool destroyed;
  unsigned int foo;
  unsigned int bar;
public:
  static MyTestObject* create();
  MyTestObject(): destroyed(false), foo(0), bar(0) {
  }
  virtual ~MyTestObject() {
    ASSERT(!destroyed, "test object destroyed twice");
    destroyed = true;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid.equals(IObject::IID)) {
      static_cast<IFoo*>(this)->addRef();
      return static_cast<IFoo*>(this);
    }

    if(uuid.equals(IFoo::IID)) {
      static_cast<IFoo*>(this)->addRef();
      return static_cast<IFoo*>(this);
    }

    if(uuid.equals(IBar::IID)) {
      static_cast<IBar*>(this)->addRef();
      return static_cast<IBar*>(this);
    }

    return 0;
  }
  void operator delete(void* self) {
    ::operator delete(self);
  }
  virtual unsigned int getFoo() {
    return foo;
  }
  virtual void setFoo(unsigned int aFoo) {
    foo = aFoo;
  }
  virtual unsigned int getBar() {
    return bar;
  }
  virtual void setBar(unsigned int aBar) {
    bar = aBar;
  }
};

MyTestObject* MyTestObject::create() {
  return new GenericComponent<MyTestObject>;
}

void test005() {
  MyTestObject* test = 0;
  IObject* iobj = 0;
  IFoo* ifoo = 0;
  IBar* ibar = 0;

  test = MyTestObject::create();
  ASSERT(test, "could not instantiate test object");

  iobj = static_cast<IFoo*>(test)->getInterface(IObject::IID);
  VERIFY(iobj, "getInterface(IObject::IID) failed on test object");

  VERIFY(reinterpret_cast<void*>(iobj) == reinterpret_cast<void*>(test), "identity test failed");

  ifoo = get<IFoo>(iobj);
  VERIFY(ifoo, "get<IFoo> failed on test object");

  ibar = get<IBar>(ifoo);
  VERIFY(ibar, "get<IBar> failed on test object");

  ifoo->setFoo(10);
  ibar->setBar(20);

  VERIFY(ifoo->getFoo() == 10, "test object has unexpected behavior");
  VERIFY(ibar->getBar() == 20, "test object has unexpected behavior");

  VERIFY(iobj->addRef() == 4, "incorrect refcount");
  VERIFY(ifoo->addRef() == 5, "incorrect refcount");
  VERIFY(ibar->addRef() == 6, "incorrect refcount");

  VERIFY(iobj->release() == 5, "incorrect refcount");
  VERIFY(ifoo->release() == 4, "incorrect refcount");
  VERIFY(ibar->release() == 3, "incorrect refcount");

  VERIFY(iobj->release() == 2, "incorrect refcount");
  VERIFY(ifoo->release() == 1, "incorrect refcount");
  VERIFY(ibar->release() == 0, "incorrect refcount");
}

