/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2001, Pierre Phaneuf
 * Copyright (C) 2000, Stéphane Lajoie
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

#include <xplc/utils.h>
#include "servmgr.h"

ServiceManager* ServiceManager::create() {
  return new GenericComponent<ServiceManager>;
}

IObject* ServiceManager::getInterface(const UUID& uuid) {
  for(;;) {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IServiceManager::IID))
      break;

    return 0;
  }

  addRef();
  return this;
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

void ServiceManager::shutdown() {
  HandlerNode* node;
  HandlerNode* ptr;

  node = handlers;
  while(node) {
    ptr = node;
    node = node->next;
    delete ptr;
  }

  handlers = 0;
}
