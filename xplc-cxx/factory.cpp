/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2003, Pierre Phaneuf
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

#include <assert.h>
#include <xplc/factory.h>
#include <xplc/utils.h>

UUID_MAP_BEGIN(GenericFactory)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IFactory)
  UUID_MAP_END

GenericFactory::GenericFactory(FactoryFunc aFactory):
  factory(aFactory) {
  assert(factory);
}

IObject* GenericFactory::createObject() {
  return factory();
}

