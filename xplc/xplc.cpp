/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
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

#include <stdlib.h>
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "servmgr.h"
#include "statichandler.h"
#include "simpledl.h"
#include "factory.h"

static IServiceManager* servmgr = NULL;
static IStaticServiceHandler* handler = NULL;

IServiceManager* XPLC::getServiceManager() {
  IObject* obj;
  IGenericFactory* factory;

  if(servmgr) {
    servmgr->addRef();
    return servmgr;
  }

  /*
   * The basic services have to be created.
   */

  servmgr = ServiceManager::create();

  if(servmgr)
    servmgr->addRef();
  else
    return NULL;

  /*
   * The static service handler could already have been created by a
   * call to XPLC::addObject.
   */
  if(!handler)
    handler = StaticServiceHandler::create();

  if(!handler) {
    servmgr->release();
    return NULL;
  }

  servmgr->addHandler(handler);

  /*
   * Populate the static service handler.
   */

  obj = GenericFactory::create();
  if(obj)
    obj->addRef();
  factory = mutateInterface<IGenericFactory>(obj);
  if(factory) {
    factory->setFactory(SimpleDynamicLoader::create);
    handler->addObject(XPLC::simpleDynamicLoader, factory);
  }

  obj = GenericFactory::create();
  if(obj)
    obj->addRef();
  factory = mutateInterface<IGenericFactory>(obj);
  if(factory) {
    factory->setFactory(GenericFactory::create);
    handler->addObject(XPLC::genericFactory, factory);
  }

  return servmgr;
}

void XPLC::addObject(const UUID& aUuid, IObject* aObj) {
  if(!handler)
    handler = StaticServiceHandler::create();

  if(handler)
    handler->addObject(aUuid, aObj);
}

void XPLC::removeObject(const UUID& aUuid) {
  if(handler)
    handler->removeObject(aUuid);
}

