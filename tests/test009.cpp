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
 */

#include "config.h"
#include <xplc/utils.h>
#include <xplc/IModuleLoader.h>
#include <xplc/IModuleManagerFactory.h>
#include "test.h"
#include "testobj.h"

/*
 * test009
 *
 * Verifies the module manager.
 */

void test009() {
#ifdef ENABLE_LOADER
  IServiceManager* servmgr;
  IObject* obj;
  IModuleManagerFactory* mgrfactory;
  IServiceHandler* modulemgr;
  ITestComponent* test;

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_moduleManagerFactory);
  ASSERT(obj != 0, "could not obtain module manager factory");

  mgrfactory = mutate<IModuleManagerFactory>(obj);
  ASSERT(mgrfactory != 0, "factory does not have expected interface");

  modulemgr = mgrfactory->createModuleManager(".");
  ASSERT(modulemgr, "could not create module manager");

  VERIFY(mgrfactory->release() == 1, "factory has wrong refcount");

  obj = modulemgr->getObject(TestComponent_CID);
  ASSERT(obj != 0, "could not create test object");

  test = mutate<ITestComponent>(obj);
  ASSERT(test != 0, "test object did not have expected interface");

  ASSERT(test->getAnswer() == 42, "test object did not have expected behavior");

  VERIFY(test->release() == 0, "test object has wrong refcount");

  VERIFY(modulemgr->release() == 0, "incorrect refcount on module loader");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
#endif
}

