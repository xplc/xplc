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
 * Verifies that the service manager queries handlers properly.
 */

const UUID obj1 = {0xd60530d8, 0x9a3d, 0x4c8e, {0xaa, 0x0b, 0x48, 0x32, 0xc6, 0x9c, 0xf0, 0x1a}};

const UUID obj2 = {0x862adfe4, 0x0821, 0x4f88, {0x85, 0x4a, 0xb9, 0xbf, 0xb9, 0xdc, 0x8a, 0x29}};

const UUID obj3 = {0xe1eabacb, 0x0795, 0x4c6d, {0x81, 0x8e, 0x7a, 0xab, 0x2c, 0x5a, 0x82, 0x25}};

class Handler1: public IServiceHandler {
public:
  static Handler1* create() {
    return new GenericComponent<Handler1>;
  }
  virtual IObject* getObject(const UUID& uuid) {
    if(uuid.equals(obj1)) {
      return reinterpret_cast<IObject*>(1);
    }

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid.equals(IObject::IID)) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid.equals(IServiceHandler::IID)) {
      addRef();
      return static_cast<IServiceHandler*>(this);
    }

    return 0;
  }
};

class Handler2: public IServiceHandler {
public:
  static Handler2* create() {
    return new GenericComponent<Handler2>;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(!uuid.equals(obj1), "request for the first object reached second handler");

    if(uuid.equals(obj2)) {
      return reinterpret_cast<IObject*>(2);
    }

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid.equals(IObject::IID)) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid.equals(IServiceHandler::IID)) {
      addRef();
      return static_cast<IServiceHandler*>(this);
    }

    return 0;
  }
};

class Handler3: public IServiceHandler {
public:
  static Handler3* create() {
    return new GenericComponent<Handler3>;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(!uuid.equals(obj1), "request for the first object reached third handler");
    VERIFY(!uuid.equals(obj2), "request for the second object reached third handler");
    if(uuid.equals(obj3)) {
      return reinterpret_cast<IObject*>(3);
    }

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid.equals(IObject::IID)) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid.equals(IServiceHandler::IID)) {
      addRef();
      return static_cast<IServiceHandler*>(this);
    }

    return 0;
  }
};

void test() {
  IServiceManager* serv;
  IServiceHandler* handler1;
  IServiceHandler* handler2;
  IServiceHandler* handler3;
  IObject* obj;

  serv = XPLC::getServiceManager();

  ASSERT(serv != 0, "could not obtain service manager");

  handler1 = Handler1::create();
  ASSERT(handler1 != 0, "could not instantiate test handler 1");
  handler1->addRef();
  serv->addFirstHandler(handler1);

  handler2 = Handler2::create();
  ASSERT(handler2 != 0, "could not instantiate test handler 2");
  handler2->addRef();
  serv->addHandler(handler2);

  handler3 = Handler3::create();
  ASSERT(handler3 != 0, "could not instantiate test handler 2");
  handler3->addRef();
  serv->addLastHandler(handler3);

  obj = serv->getObject(obj1);
  VERIFY(obj != 0, "object 1 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(1), "asked for object 1 and got another one");

  obj = serv->getObject(obj2);
  VERIFY(obj != 0, "object 2 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(2), "asked for object 2 and got another one");

  obj = serv->getObject(obj3);
  VERIFY(obj != 0, "object 3 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(3), "asked for object 3 and got another one");

  serv->removeHandler(handler1);
  serv->removeHandler(handler2);
  serv->removeHandler(handler3);

  obj = serv->getObject(obj1);
  VERIFY(!obj, "object 1 still returned after removing handler 1");

  obj = serv->getObject(obj2);
  VERIFY(!obj, "object 2 still returned after removing handler 2");

  obj = serv->getObject(obj3);
  VERIFY(!obj, "object 3 still returned after removing handler 3");

  serv->shutdown();

  VERIFY(serv->release() == 0, "service manager has non-zero refcount after shutdown/release");
}
