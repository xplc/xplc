/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2000, Stéphane Lajoie
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

#include <xplc/core.h>
#include <xplc/utils.h>
#include "servmgr.h"
#include "statichandler.h"
#include "moduleloader.h"
#include "singleloader.h"
#include "factory.h"
#include "monikers.h"
#include "new.h"

UUID_MAP_BEGIN(ServiceManager)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceManager)
  UUID_MAP_END

static ServiceManager* singleton;

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

  servmgr = ServiceManager::obtain();
  if(!servmgr)
    return 0;

  obj = servmgr->getObject(XPLC_staticServiceHandler);
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
    handler->addObject(XPLC_staticServiceHandler, handler2);
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
    handler->addObject(XPLC_genericFactory, factory);
  }

  /* Create moniker service and register monikers. */
  monikers = MonikerService::create();
  if(monikers) {
    monikers->addRef();

    monikers->registerObject("new", XPLC_newMoniker);

    handler->addObject(XPLC_monikers, monikers);

    monikers->release();
  }

  /*
   * We will use the factory to create the other factories.
   */
  factoryfactory = factory;

  factory = mutate<IGenericFactory>(factoryfactory->createObject());
  if(factory) {
    factory->setFactory(SingleModuleLoader::create);
    handler->addObject(XPLC_singleModuleLoader, factory);
    factory->release();
  }

  factory = mutate<IGenericFactory>(factoryfactory->createObject());
  if(factory) {
    factory->setFactory(ModuleLoader::create);
    handler->addObject(XPLC_moduleLoader, factory);
    factory->release();
  }

  factoryfactory->release();

  handler->addObject(XPLC_newMoniker, NewMoniker::create());

  return servmgr;
}

ServiceManager* ServiceManager::obtain() {
  if(!singleton)
    singleton = new GenericComponent<ServiceManager>;

  if(singleton)
    singleton->addRef();

  return singleton;
}

ServiceManager::~ServiceManager() {
  HandlerNode* next;

  while(handlers) {
    next = handlers->next;
    delete handlers;
    handlers = next;
  }

  if(singleton == this)
    singleton = 0;
}

void ServiceManager::addHandler(IServiceHandler* aHandler) {
  HandlerNode* node;
  HandlerNode** ptr;

  ptr = &handlers;
  node = *ptr;
  while(node) {
    if(node->handler == aHandler)
      break;

    if(node->intercept) {
      ptr = &node->next;
    }
    node = node->next;
  }

  /*
   * The handler is already there.
   */
  if(node)
    return;

  node = new HandlerNode(aHandler, *ptr, false);
  *ptr = node;
}

void ServiceManager::addFirstHandler(IServiceHandler* aHandler) {
  HandlerNode* node;

  node = handlers;
  while(node) {
    if(node->handler == aHandler)
      break;

    node = node->next;
  }

  /*
   * The handler is already there.
   */
  if(node)
    return;

  node = new HandlerNode(aHandler, handlers, true);
  handlers = node;
}

void ServiceManager::addLastHandler(IServiceHandler* aHandler) {
  HandlerNode* node;
  HandlerNode** ptr;

  ptr = &handlers;
  node = *ptr;
  while(node) {
    if(node->handler == aHandler)
      break;

    ptr = &node->next;
    node = *ptr;
  }

  /*
   * The handler is already there.
   */
  if(node)
    return;

  node = new HandlerNode(aHandler, *ptr, false);
  *ptr = node;
}

void ServiceManager::removeHandler(IServiceHandler* aHandler) {
  HandlerNode* node;
  HandlerNode** ptr;

  node = handlers;
  ptr = &handlers;
  while(node) {
    if(node->handler == aHandler) {
      *ptr = node->next;
      delete node;
      break;
    }

    ptr = &node->next;
    node = *ptr;
  }
}

IObject* ServiceManager::getObject(const UUID& aUuid) {
  IObject* obj;
  HandlerNode* handler;

  handler = handlers;
  while(handler) {
    obj = handler->handler->getObject(aUuid);

    /*
     * No need to addRef the object, the handler does it for us.
     */
    if(obj)
      return obj;

    handler = handler->next;
  }

  return 0;
}

