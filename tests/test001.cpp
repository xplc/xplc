/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
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

#include "test.h"
#include <xplc/utils.h>

/*
 * test001
 *
 * Verifies that the service manager queries handlers properly.
 */

const UUID obj1 = {0xd60530d8, 0x9a3d, 0x4c8e, {0xaa, 0x0b, 0x48, 0x32, 0xc6, 0x9c, 0xf0, 0x1a}};

const UUID obj2 = {0x862adfe4, 0x0821, 0x4f88, {0x85, 0x4a, 0xb9, 0xbf, 0xb9, 0xdc, 0x8a, 0x29}};

const UUID obj3 = {0xe1eabacb, 0x0795, 0x4c6d, {0x81, 0x8e, 0x7a, 0xab, 0x2c, 0x5a, 0x82, 0x25}};

class Handler1: public IServiceHandler {
  IMPLEMENT_IOBJECT(Handler1);
public:
  static Handler1* create() {
    return new Handler1;
  }
  virtual IObject* getObject(const UUID& uuid) {
    if(uuid == obj1) {
      return reinterpret_cast<IObject*>(1);
    }

    return 0;
  }
};

class Handler2: public IServiceHandler {
  IMPLEMENT_IOBJECT(Handler2);
public:
  static Handler2* create() {
    return new Handler2;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(uuid != obj1, "request for the first object reached second handler");

    if(uuid == obj2) {
      return reinterpret_cast<IObject*>(2);
    }

    return 0;
  }
};

class Handler3: public IServiceHandler {
  IMPLEMENT_IOBJECT(Handler3);
public:
  static Handler3* create() {
    return new Handler3;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(uuid != obj1, "request for the first object reached third handler");
    VERIFY(uuid != obj2, "request for the second object reached third handler");
    if(uuid == obj3) {
      return reinterpret_cast<IObject*>(3);
    }

    return 0;
  }
};

UUID_MAP_BEGIN(Handler1)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_END

UUID_MAP_BEGIN(Handler2)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_END

UUID_MAP_BEGIN(Handler3)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_END

void test001() {
  IServiceManager* serv;
  IServiceHandler* handler1;
  IServiceHandler* handler2;
  IServiceHandler* handler3;
  IObject* obj;

  serv = XPLC_getServiceManager();

  ASSERT(serv != 0, "could not obtain service manager");

  handler1 = Handler1::create();
  ASSERT(handler1 != 0, "could not instantiate test handler 1");
  serv->addFirstHandler(handler1);

  handler2 = Handler2::create();
  ASSERT(handler2 != 0, "could not instantiate test handler 2");
  serv->addHandler(handler2);

  handler3 = Handler3::create();
  ASSERT(handler3 != 0, "could not instantiate test handler 2");
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

  VERIFY(handler1->release() == 0, "incorrect refcount on handler 1");
  VERIFY(handler2->release() == 0, "incorrect refcount on handler 2");
  VERIFY(handler3->release() == 0, "incorrect refcount on handler 3");

  VERIFY(serv->release() == 0, "service manager has non-zero refcount after release");
}
