/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#include <stddef.h>
#include <xplc/utils.h>
#include "factory.h"

UUID_MAP_BEGIN(GenericFactory)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IFactory)
  UUID_MAP_ENTRY(IGenericFactory)
  UUID_MAP_END

IObject* GenericFactory::create() {
  return new GenericComponent<GenericFactory>;
}

IObject* GenericFactory::createObject() {
  IObject* obj;

  obj = factory();

  if(obj)
    obj->addRef();

  return obj;
}

void GenericFactory::setFactory(IObject*(*aFactory)()) {
  factory = aFactory;
}
