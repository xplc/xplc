/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
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

#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "statichandler.h"
#include "moduleloader.h"
#include "singleloader.h"
#include "factory.h"
#include "monikers.h"
#include "new.h"
#include "servmgr.h"

IServiceManager* XPLC_getServiceManager() {
  IServiceManager* servmgr;
  IObject* obj;
  IStaticServiceHandler* handler;
  IStaticServiceHandler* handler2;
  IGenericFactory* factory;
  IFactory* factoryfactory;
  IMonikerService* monikers;

  /*
   * The basic services have to be created.
   */

  servmgr = XPLC_getCoreServiceManager();
  if(!servmgr)
    return 0;

  obj = servmgr->getObject(XPLC::staticServiceHandler);
  if(obj) {
    obj->release();
    return servmgr;
  }

  handler = StaticServiceHandler::create();

  if(!handler) {
    servmgr->release();
    return 0;
  }

  servmgr->addHandler(handler);

  /*
   * Populate the static service handler.
   */

  handler2 = StaticServiceHandler::create();
  if(handler2) {
    handler->addObject(XPLC::staticServiceHandler, handler2);
    servmgr->addHandler(handler2);
  } else {
    servmgr->release();
    return 0;
  }

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

  handler->addObject(XPLC::newMoniker, NewMoniker::create());

  return servmgr;
}
