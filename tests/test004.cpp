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
#include <xplc/config.h>
#include <xplc/utils.h>
#include <xplc/ISingleModuleLoader.h>
#include "testobj.h"

/*
 * test004
 *
 * Verifies the single module loader.
 */

void test004() {
#ifdef ENABLE_LOADER
  IServiceManager* servmgr;
  IFactory* loaderfactory;
  IObject* obj;
  ISingleModuleLoader* loader;
  ITestComponent* test;
  const char* err;

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_singleModuleLoader);
  ASSERT(obj != 0, "could not obtain single module loader component");

  loaderfactory = mutate<IFactory>(obj);
  ASSERT(loaderfactory != 0, "factory does not have expected interface");

  obj = loaderfactory->createObject();
  ASSERT(obj != 0, "could not create single module loader component");

  VERIFY(loaderfactory->release() == 1, "single module loader factory has wrong refcount");

  loader = mutate<ISingleModuleLoader>(obj);
  ASSERT(loader != 0, "single module loader does not have expected interface");

  err = loader->loadModule("./testobj.dll");
  ASSERT(!err, err);

  obj = loader->getObject(TestComponent_CID);
  ASSERT(obj != 0, "could not create test object");

  test = mutate<ITestComponent>(obj);
  ASSERT(test != 0, "test object did not have expected interface");

  ASSERT(test->getAnswer() == 42, "test object did not have expected behavior");

  VERIFY(test->release() == 1, "test object has wrong refcount");

  VERIFY(loader->release() == 0, "single module loader has wrong refcount");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
#endif
}
