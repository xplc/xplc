/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#include <xplc/IFactory.h>
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "new.h"

static NewMoniker* singleton = 0;

NewMoniker* NewMoniker::obtain() {
  if(!singleton)
    singleton = new GenericComponent<NewMoniker>;

  return singleton;
}

NewMoniker::~NewMoniker() {
  singleton = 0;
}

IObject* NewMoniker::getInterface(const UUID& uuid) {
  for(;;) {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IMoniker::IID))
      break;

    return 0;
  }

  addRef();
  return this;
}

IObject* NewMoniker::resolve(const char* aName) {
  IServiceManager* servmgr;
  IMoniker* monikers;
  IFactory* factory;
  IObject* obj = 0;

  servmgr = XPLC::getServiceManager();
  if(servmgr) {
    monikers = mutate<IMoniker>(servmgr->getObject(XPLC::monikers));

    if(monikers) {
      factory = mutate<IFactory>(monikers->resolve(aName));

      if(factory) {
        obj = factory->createObject();
        factory->release();
      }

      monikers->release();
    }

    servmgr->release();
  }

  return obj;
}

