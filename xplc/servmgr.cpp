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
#include "servmgr.h"

IObject* ServiceManager::getInterface(const UUID& uuid) {
  do {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IServiceManager::IID))
      break;

    return NULL;
  } while(0);

  addRef();
  return this;
}

void ServiceManager::addObject(const UUID& aUuid, IObject* aObj) {
  ObjectNode* node;

  node = objects;
  while(node) {
    if(node->uuid.equals(aUuid))
      break;

    node = node->next;
  }

  /*
   * FIXME: maybe add a "replace" bool parameter? Or would this
   *  encourage UUID hijacking too much?
   */
  if(node)
    return;

  node = new ObjectNode(aUuid, aObj, objects);
  objects = node;
}

void ServiceManager::removeObject(const UUID& aUuid) {
  ObjectNode* node;
  ObjectNode** ptr;

  node = objects;
  ptr = &objects;
  while(node) {
    if(node->uuid.equals(aUuid)) {
      *ptr = node->next;
      delete node;
      break;
    }

    ptr = &node->next;
    node = *ptr;
  }
}

IObject* ServiceManager::getObject(const UUID& aUuid) {
  ObjectNode* obj;

  /*
   * We look through the objects list and return if we find a match.
   */
  obj = objects;
  while(obj) {
    if(obj->uuid.equals(aUuid)) {
      obj->obj->addRef();
      return obj->obj;
    }

    obj = obj->next;
  }

  /*
   * No match was found, we return empty-handed.
   */
  return NULL;
}

void ServiceManager::shutdown() {
  ObjectNode* node;
  ObjectNode* ptr;

  node = objects;
  while(node) {
    ptr = node;
    node = node->next;
    delete ptr;
  }
  objects = NULL;
}

