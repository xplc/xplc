/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Net Integration Technologies, Inc.
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

#include <xplc/IMoniker.h>
#include <xplc/xplc.h>
#include <xplc/ptr.h>

IObject* XPLC::create(const UUID& cid) {
  xplc_ptr<IFactory> factory;

  if(!servmgr)
    return 0;

  factory = servmgr->getObject(cid);
  if(!factory)
    return 0;

  return factory->createObject();
}

IObject* XPLC::create(const char* aMoniker) {
  xplc_ptr<IMoniker> moniker;
  xplc_ptr<IFactory> factory;

  if(!servmgr)
    return 0;

  moniker = servmgr->getObject(XPLC_monikers);
  if(!moniker)
    return 0;

  factory = moniker->resolve(aMoniker);
  if(!factory)
    return 0;

  return factory->createObject();
}

XPLC::~XPLC() {
  if(servmgr)
    servmgr->release();
}

