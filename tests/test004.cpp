/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2004, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#include "test.h"
#include "config.h"
#include <xplc/utils.h>
#include <xplc/IModuleLoader.h>
#include "testobj.h"

/*
 * test004
 *
 * Verifies the module loader.
 */

void test004() {
#ifdef ENABLE_LOADER
  IServiceManager* servmgr;
  IModuleLoader* loader;
  IModule* module;
  IObject* obj;
  ITestComponent* test;

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_moduleLoader);
  ASSERT(obj != 0, "could not obtain the module loader component");

  loader = mutate<IModuleLoader>(obj);
  ASSERT(loader != 0, "module loader does not have expected interface");

  module = loader->loadModule("./testobj.dll");
  ASSERT(module, "could not load module");

  VERIFY(loader->release() == 1, "module loader factory has wrong refcount");

  obj = module->getObject(TestComponent_CID);
  ASSERT(obj != 0, "could not create test object");

  test = mutate<ITestComponent>(obj);
  ASSERT(test != 0, "test object did not have expected interface");

  ASSERT(test->getAnswer() == 42, "test object did not have expected behavior");

  VERIFY(test->release() == 0, "test object has wrong refcount");

  VERIFY(module->release() == 0, "module has wrong refcount");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
#endif
}

