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

#include "../test.h"
#include <xplc/xplc.h>
#include <xplc/utils.h>

/*
 * test002
 *
 * Verifies add, get and remove operations on the service manager.
 */

class IFoo: public IObject {
public:
  static const UUID IID;
  virtual void setFoo(int) = 0;
  virtual void incFoo() = 0;
  virtual int getFoo() = 0;
};

const UUID IFoo::IID __attribute__((weak)) = {0xb5633a54, 0xf900, 0x4601, {0xa5, 0xa4, 0xc0, 0x1a, 0x0c, 0x98, 0x26, 0x06}};

class Foo: public IFoo {
private:
  int foo;
public:
  Foo(): foo(0) {};
  /* IObject */
  virtual IObject* getInterface(const UUID&);
  /* IFoo */
  virtual void setFoo(int);
  virtual void incFoo();
  virtual int getFoo();
};

IObject* Foo::getInterface(const UUID& uuid) {
  do {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IFoo::IID))
      break;

    return NULL;
  } while(0);

  addRef();
  return this;
}

void Foo::setFoo(int aFoo) {
  foo = aFoo;
}

void Foo::incFoo() {
  foo++;
}

int Foo::getFoo() {
  return foo;
}

void test() {
  IServiceManager* serv;
  Foo* foo;
  IFoo* ifoo;
  IObject* obj;
  const UUID foouuid = {0x696bdfba, 0x9b5e, 0x4bcd, {0xaf, 0x10, 0x39, 0x94, 0x92, 0x94, 0x92, 0x3b}};

  serv = XPLC::getServiceManager();

  ASSERT(serv, "could not obtain service manager");

  foo = new GenericComponent<Foo>;
  ASSERT(foo, "could not instantiate test component");

  serv->addObject(foouuid, foo);

  obj = serv->getObject(foouuid);
  ASSERT(obj, "could not get component from the service manager");

  ifoo = mutateInterface<IFoo>(obj);
  ASSERT(ifoo, "test component does not have expected interface");

  ifoo->setFoo(10);
  ifoo->incFoo();
  VERIFY(ifoo->getFoo() == 11, "test component has unexpected behavior");

  ifoo->release();

  serv->removeObject(foouuid);

  obj = serv->getObject(foouuid);
  VERIFY(!obj, "service manager did not remove the test component");

  serv->shutdown();

  VERIFY(serv->release() == 0, "service manager has non-zero refcount after shutdown/release");
}
