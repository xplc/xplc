/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
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

#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "servmgr.h"
#include "statichandler.h"
#include "moduleloader.h"
#include "singleloader.h"
#include "factory.h"
#include "monikers.h"
#include "new.h"

static ServiceManager* servmgr = 0;

IServiceManager* XPLC::getServiceManager() {
  IObject* obj;
  IStaticServiceHandler* handler;
  IGenericFactory* factory;
  IFactory* factoryfactory;
  IMonikerService* monikers;

  if(servmgr) {
    servmgr->addRef();
    return servmgr;
  }

  /*
   * The basic services have to be created.
   */

  ServiceManager::create(&servmgr);

  if(servmgr)
    servmgr->addRef();
  else
    return 0;

  handler = StaticServiceHandler::create();

  if(!handler) {
    servmgr->release();
    return 0;
  }

  servmgr->addHandler(handler);

  /*
   * Populate the static service handler.
   */

  handler->addObject(XPLC::staticServiceHandler, handler);

  obj = GenericFactory::create();
  if(obj)
    obj->addRef();
  factory = mutate<IGenericFactory>(obj);
  if(factory) {
    factory->setFactory(GenericFactory::create);
    handler->addObject(XPLC::genericFactory, factory);
  }

  /* Create moniker service and register monikers. */
  monikers = MonikerService::create();
  if(monikers) {
    monikers->addRef();

    monikers->registerObject("new", XPLC::newMoniker);

    handler->addObject(XPLC::monikers, monikers);

    monikers->release();
  }

  /*
   * We will use the factory to create the other factories.
   */
  factoryfactory = factory;

  factory = mutate<IGenericFactory>(factoryfactory->createObject());
  if(factory) {
    factory->setFactory(SingleModuleLoader::create);
    handler->addObject(XPLC::singleModuleLoader, factory);
    factory->release();
  }

  factory = mutate<IGenericFactory>(factoryfactory->createObject());
  if(factory) {
    factory->setFactory(ModuleLoader::create);
    handler->addObject(XPLC::moduleLoader, factory);
    factory->release();
  }

  factoryfactory->release();

  handler->addObject(XPLC::newMoniker, NewMoniker::obtain());

  return servmgr;
}
