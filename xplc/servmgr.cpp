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

unsigned int ServiceManager::addRef() {
  return ++refcount;
}

unsigned int ServiceManager::release() {
  if(--refcount)
    return refcount;

  /* protect against re-entering the destructor */
  refcount = 1;

  delete this;

  return 0;
}

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

void ServiceManager::registerUuid(const UUID&, IObject*) {
}

void ServiceManager::unregisterUuid(const UUID&) {
}

IObject* ServiceManager::getObjectByUuid(const UUID&) {
  return NULL;
}

void ServiceManager::shutdown() {
}

