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
#include <xplc/core.h>
#include <xplc/module.h>
#include <xplc/utils.h>
#include "loader.h"
#include "singleloader.h"

UUID_MAP_BEGIN(SingleModuleLoader)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_ENTRY(ISingleModuleLoader)
  UUID_MAP_END

IObject* SingleModuleLoader::create() {
  return new GenericComponent<SingleModuleLoader>;
}

SingleModuleLoader::~SingleModuleLoader() {
  if(module)
    module->release();

  if(dlh)
    loaderClose(dlh);
}

IObject* SingleModuleLoader::getObject(const UUID& uuid) {
  if(module)
    return module->getObject(uuid);
  else
    return 0;
}

const char* SingleModuleLoader::loadModule(const char* filename) {
  const char* err;
  XPLC_GetModuleFunc getmodule = 0;
  IServiceManager* servmgr;

  if(module) {
    module->release();
    module = 0;
  }

  if(dlh)
    loaderClose(dlh);

  err = loaderOpen(filename, &dlh);
  if(err)
    return err;

  err = loaderSymbol(dlh, "XPLC_GetModule",
                     reinterpret_cast<void**>(&getmodule));
  if(err) {
    loaderClose(dlh);
    dlh = 0;
    return err;
  }

  if(!getmodule) {
    loaderClose(dlh);
    dlh = 0;
    return "could not find XPLC_GetModule entry point";
  }

  servmgr = XPLC_getServiceManager();

  module = getmodule(servmgr, XPLC_MODULE_VERSION);
  if(!module) {
    loaderClose(dlh);
    dlh = 0;
    return "could not obtain module";
  }

  if(servmgr)
    servmgr->release();

  return 0;
}

