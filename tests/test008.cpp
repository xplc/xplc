/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2001-2002, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
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
#include <xplc/IStaticServiceHandler.h>
#include <xplc/IMonikerService.h>
#include <xplc/utils.h>

/*
 * test008
 *
 * Verifies the "new" moniker
 */

void test008() {
  IServiceManager* servmgr;
  IStaticServiceHandler* handler;
  IMonikerService* monikers;
  ITestInterface* test;
  TestObjectFactory* factory;
  IObject* obj;

  servmgr = XPLC::getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC::staticServiceHandler);
  ASSERT(obj != 0, "could not obtain static service handler");

  handler = mutate<IStaticServiceHandler>(obj);
  ASSERT(handler != 0, "static service handler does not have the IStaticServiceHandler interface");

  factory = new TestObjectFactory;
  ASSERT(factory != 0, "could not instantiate test object factory");
  factory->addRef();

  handler->addObject(TestObjectFactory_CID, factory);
  VERIFY(servmgr->getObject(TestObjectFactory_CID) == factory, "adding the test object factory did not work");
  VERIFY(factory->release() == 2, "incorrect refcount on test object factory");

  monikers = mutate<IMonikerService>(servmgr->getObject(XPLC::monikers));
  ASSERT(monikers != 0, "could not obtain correct moniker service");

  monikers->registerObject("testobject", TestObjectFactory_CID);

  obj = monikers->resolve("new:testobject");
  ASSERT(obj != 0, "could not obtain test object");

  test = get<ITestInterface>(obj);
  VERIFY(test != 0, "test object does not have ITestInterface");
  VERIFY(test->release() == 1, "incorrect refcount on test object");

  VERIFY(obj->release() == 0, "incorrect refcount on test object");

  servmgr->shutdown();
  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after shutdown/release");

  VERIFY(factory->release() == 0, "incorrect refcount on test object factory");
}
