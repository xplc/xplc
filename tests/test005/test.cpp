/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#include "../test.h"
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include <xplc/ISimpleDynamicLoader.h>
#include "testobj.h"

/*
 * test005
 *
 * Verifies the simple dynamic component loader.
 */

void test() {
  IServiceManager* servmgr;
  IFactory* dynfactory;
  IObject* obj;
  ISimpleDynamicLoader* dyn;
  ITestComponent* test;
  const char* err;

  servmgr = XPLC::getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC::simpleDynamicLoader);
  ASSERT(obj != 0, "could not obtain simple dynamic loader component");

  dynfactory = mutate<IFactory>(obj);
  ASSERT(dynfactory != 0, "factory does not have expected interface");

  obj = dynfactory->createObject();
  ASSERT(obj != 0, "could not create simple dynamic loader component");

  dyn = mutate<ISimpleDynamicLoader>(obj);
  ASSERT(dyn != 0, "simple dynamic loader does not have expected interface");

  err = dyn->loadModule("tests/test005/testobj.dll");
  ASSERT(!err, err);

  obj = dyn->getObject(TestComponent_CID);
  ASSERT(obj != 0, "could not create test object");

  test = mutate<ITestComponent>(obj);
  ASSERT(test != 0, "test object did not have expected interface");

  ASSERT(test->getAnswer() == 42, "test object did not have expected behavior");

  VERIFY(test->release() == 1, "test object has wrong refcount");

  servmgr->shutdown();

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after shutdown/release");
}
