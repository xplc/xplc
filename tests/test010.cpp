/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2003, Pierre Phaneuf
 * Copyright (C) 2003, Net Integration Technologies, Inc.
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

#include <string.h>
#include <xplc/ICategoryManager.h>
#include <xplc/IModuleManagerFactory.h>
#include <xplc/utils.h>
#include "test.h"
#include "testobj.h"
#include "config.h"

/*
 * test010
 *
 * Tests categories.
 */

static const UUID myComponent1 = {0xb4a924ca, 0x0b81, 0x48de,
                                  {0xb6, 0x61, 0x5c, 0x63,
                                   0x54, 0xcc, 0xa0, 0xac}};

static const UUID myComponent2 = {0x02080213, 0x37f7, 0x4961,
                                  {0x85, 0x2e, 0x78, 0x97,
                                   0x51, 0x9c, 0xfa, 0x49}};

static const UUID myComponent3 = {0xea511e95, 0x5be4, 0x4b08,
                                  {0x86, 0xca, 0xad, 0xd5,
                                   0x9a, 0xf7, 0xe2, 0x94}};

#ifdef ENABLE_LOADER
#define NUM_CATITEM 4
#else
#define NUM_CATITEM 3
#endif

void test010() {
  IServiceManager* servmgr;
  IObject* obj;
  ICategoryManager* catmgr;
  ICategory* cat;
  ICategoryIterator* iter;
  unsigned int num;
  bool seen[NUM_CATITEM];
#ifdef ENABLE_LOADER
  IModuleManagerFactory* mgrfactory;
  IServiceHandler* modulemgr;
#endif

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_categoryManager);
  ASSERT(obj != 0, "could not obtain category manager");

  catmgr = mutate<ICategoryManager>(obj);
  ASSERT(catmgr != 0, "category manager does not have expected interface");

#ifdef ENABLE_LOADER
  obj = servmgr->getObject(XPLC_moduleManagerFactory);
  ASSERT(obj != 0, "could not obtain module manager factory");

  mgrfactory = mutate<IModuleManagerFactory>(obj);
  ASSERT(mgrfactory != 0, "factory does not have expected interface");

  modulemgr = mgrfactory->createModuleManager(".");
  ASSERT(modulemgr, "could not create module manager");

  VERIFY(mgrfactory->release() == 1, "factory has wrong refcount");
#endif

  catmgr->registerComponent(testCategory, myComponent1, "myComponent1");
  catmgr->registerComponent(testCategory, myComponent2, "myComponent2");
  catmgr->registerComponent(testCategory, myComponent3, 0);

  cat = catmgr->getCategory(testCategory);
  ASSERT(cat, "could not obtain the category");

  for(num = 0; num < NUM_CATITEM; ++num) {
    seen[num] = false;
  }

  iter = cat->getIterator();

  ASSERT(iter, "could not obtain the category iterator");

  num = 0;
  for(; !iter->done(); iter->next()) {
    ++num;

    if(iter->getUuid() == myComponent1) {
      VERIFY(!seen[0], "myComponent1 already seen");
      VERIFY(iter->getString()
             && strcmp(iter->getString(), "myComponent1") == 0,
             "incorrect string for myComponent1");
      seen[0] = true;
    } else if(iter->getUuid() == myComponent2) {
      VERIFY(!seen[1], "myComponent2 already seen");
      VERIFY(iter->getString()
             && strcmp(iter->getString(), "myComponent2") == 0,
             "incorrect string for myComponent2");
      seen[1] = true;
    } else if(iter->getUuid() == myComponent3) {
      VERIFY(!seen[2], "myComponent3 already seen");
      VERIFY(!iter->getString(), "incorrect string for myComponent3");
      seen[2] = true;
#ifdef ENABLE_LOADER
    } else if(iter->getUuid() == TestComponent_CID) {
      VERIFY(!seen[3], "TestComponent already seen");
      VERIFY(iter->getString()
             && strcmp(iter->getString(), "TestComponent") == 0,
             "incorrect string for TestComponent");
      seen[3] = true;
#endif
    } else {
      VERIFY(false, "got an unknown component");
    }
  }

  VERIFY(iter->release() == 0, "category iterator has wrong refcount");
  VERIFY(num == NUM_CATITEM, "the category has an incorrect number of items");

  VERIFY(cat->release() == 0, "category has wrong refcount");

#ifdef ENABLE_LOADER
  VERIFY(modulemgr->release() == 0, "incorrect refcount on module loader");
#endif

  VERIFY(catmgr->release() == 1, "category manager has wrong refcount");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
}

