/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2001-2002, Pierre Phaneuf
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
#include <xplc/IStaticServiceHandler.h>
#include <xplc/IMonikerService.h>

/*
 * test006
 *
 * Verifies the moniker facility
 */

void test006() {
  IServiceManager* servmgr;
  IStaticServiceHandler* handler;
  IMonikerService* monikers;
  IObject* testobj;
  IObject* obj;

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_staticServiceHandler);
  ASSERT(obj != 0, "could not obtain static service handler");

  handler = mutate<IStaticServiceHandler>(obj);
  ASSERT(handler != 0, "static service handler does not have the IStaticServiceHandler interface");

  testobj = new TestObject;
  ASSERT(testobj != 0, "could not create TestObject");
  testobj->addRef();

  handler->addObject(TestObject_CID, testobj);
  VERIFY(servmgr->getObject(TestObject_CID) == testobj, "adding the test object did not work");
  VERIFY(testobj->release() == 2, "incorrect refcount on test object");

  obj = servmgr->getObject(XPLC_monikers);
  ASSERT(obj != 0, "could not obtain moniker component");
  
  monikers = mutate<IMonikerService>(obj);
  ASSERT(monikers != 0, "moniker service does not have the IMoniker interface");
  monikers->registerObject("moniker", XPLC_monikers);
  monikers->registerObject("testobject", TestObject_CID);

  obj = monikers->resolve("testobject");
  ASSERT(obj != 0, "resolving the test object returned nothing");
  ASSERT(obj == testobj, "the testobject moniker resolved to something else than the test object");
  VERIFY(obj->release() == 2, "refcount is wrong on the test object");

  obj = monikers->resolve("moniker:testobject");
  ASSERT(obj != 0, "resolving the test object indirectly returned nothing");
  ASSERT(obj == testobj, "the testobject moniker indirectly resolved to something else than the test object");
  VERIFY(obj->release() == 2, "refcount is wrong on the test object");

  obj = monikers->resolve("moniker:");
  VERIFY(obj == 0, "resolving an empty sub-moniker returned something");

  VERIFY(monikers->release() == 1, "incorrect refcount on moniker service");

  VERIFY(handler->release() == 2, "incorrect refcount on static service handler");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");

  VERIFY(testobj->release() == 0, "refcount is wrong on the test object");

  delete testobj;
}

