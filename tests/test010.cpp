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

#include <xplc/ICategoryManager.h>
#include <xplc/utils.h>
#include "test.h"

/*
 * test010
 *
 * Tests categories.
 */

static const UUID myCategory = {0x14b4b499, 0xc5f3, 0x42c1,
                                {0x9e, 0x9b, 0x91, 0x9e,
                                 0x6a, 0xd2, 0xe9, 0xe9}};

static const UUID myComponent1 = {0xb4a924ca, 0x0b81, 0x48de,
                                  {0xb6, 0x61, 0x5c, 0x63,
                                   0x54, 0xcc, 0xa0, 0xac}};

static const UUID myComponent2 = {0x02080213, 0x37f7, 0x4961,
                                  {0x85, 0x2e, 0x78, 0x97,
                                   0x51, 0x9c, 0xfa, 0x49}};

static const UUID myComponent3 = {0xea511e95, 0x5be4, 0x4b08,
                                  {0x86, 0xca, 0xad, 0xd5,
                                   0x9a, 0xf7, 0xe2, 0x94}};

static const UUID myComponent4 = {0xeb0d310e, 0x38f7, 0x465d,
                                  {0x8c, 0xd0, 0xfd, 0x97,
                                   0x0c, 0xf8, 0xbd, 0x26}};


void test010() {
  IServiceManager* servmgr;
  IObject* obj;
  ICategoryManager* catmgr;
  ICategory* cat;
  unsigned int num;
  bool seen[3] = { false, false, false };

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC_categoryManager);
  ASSERT(obj != 0, "could not obtain category manager");

  catmgr = mutate<ICategoryManager>(obj);
  ASSERT(catmgr != 0, "category manager does not have expected interface");

  catmgr->registerComponent(myCategory, myComponent1);
  catmgr->registerComponent(myCategory, myComponent2);
  catmgr->registerComponent(myCategory, myComponent3);

#if 0
  cat = catmgr->getCategory(myCategory);
  ASSERT(cat, "could not obtain the category");

  catmgr->registerComponent(myCategory, myComponent4);

  num = cat->numEntries();
  VERIFY(num == 3, "the category has an incorrect number of items");

  for(unsigned int i = 0; i < num; ++i) {
    ICategoryEntry* item = cat->getEntry(i);
    ASSERT(item, "could not get a category entry");

    VERIFY(!item->getUuid().equals(myComponent4),
           "incorrectly got myComponent4");

    if(item->getUuid().equals(myComponent1)) {
      VERIFY(!seen[0], "myComponent1 already seen");
      seen[0] = true;
    } else if(item->getUuid().equals(myComponent2)) {
      VERIFY(!seen[1], "myComponent2 already seen");
      seen[1] = true;
    } else if(item->getUuid().equals(myComponent3)) {
      VERIFY(!seen[2], "myComponent3 already seen");
      seen[2] = true;
    } else {
      VERIFY(false, "got an unknown component");
    }

    VERIFY(item->release() == 0, "category item has wrong refcount");
  }

  VERIFY(cat->release() == 0, "category has wrong refcount");
#endif

  VERIFY(catmgr->release() == 1, "category manager has wrong refcount");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
}

