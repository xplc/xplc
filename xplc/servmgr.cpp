/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
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
#include "catmgr.h"
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

static void add_factory(IStaticServiceHandler* handler,
                        const UUID& uuid,
                        IObject*(*factoryptr)()) {
  IGenericFactory* factory = new GenericComponent<GenericFactory>;

  if(factory) {
    factory->setFactory(factoryptr);
    handler->addObject(uuid, factory);
  }
}

IServiceManager* XPLC_getServiceManager() {
  if(!singleton) {
    IStaticServiceHandler* handler;
    IStaticServiceHandler* handler2;
    IMonikerService* monikers;

    singleton = new GenericComponent<ServiceManager>;

    if(!singleton)
      return 0;

    handler = new GenericComponent<StaticServiceHandler>;
    if(!handler) {
      singleton->addRef();
      singleton->release();
      return 0;
    }

    /*
     * Populate the static service handler.
     */

    handler2 = new GenericComponent<StaticServiceHandler>;
    if(handler2) {
      handler->addObject(XPLC_staticServiceHandler, handler2);
      singleton->addHandler(handler2);
    } else {
      singleton->addRef();
      singleton->release();
      return 0;
    }

    handler->addObject(XPLC_newMoniker, new GenericComponent<NewMoniker>);
    handler->addObject(XPLC_categoryManager,
                       new GenericComponent<CategoryManager>);

    monikers = new GenericComponent<MonikerService>;
    if(monikers) {
      monikers->registerObject("new", XPLC_newMoniker);
      handler->addObject(XPLC_monikers, monikers);
    }

    add_factory(handler, XPLC_genericFactory,
                GenericComponent<GenericFactory>::create);

    add_factory(handler, XPLC_singleModuleLoader,
                GenericComponent<SingleModuleLoader>::create);

    add_factory(handler, XPLC_moduleLoader,
                GenericComponent<ModuleLoader>::create);

    singleton->addHandler(handler);
  }

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

