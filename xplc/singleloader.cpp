/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
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
#include "moduleloader.h"
#include "singleloader.h"

UUID_MAP_BEGIN(SingleModuleLoader)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_ENTRY(ISingleModuleLoader)
  UUID_MAP_END

SingleModuleLoader::~SingleModuleLoader() {
  if(dlh)
    loaderClose(dlh);
}

IObject* SingleModuleLoader::getObject(const UUID& uuid) {
  if(info)
    return getModuleObject(info->components, uuid);

  return 0;
}

const char* SingleModuleLoader::loadModule(const char* filename) {
  const XPLC_ModuleInfo* moduleinfo;
  const char* err;

  if(dlh)
    loaderClose(dlh);

  err = loaderOpen(filename, &dlh);
  if(err)
    return err;

  err = loaderSymbol(dlh, "XPLC_Module",
                     reinterpret_cast<void**>(const_cast<XPLC_ModuleInfo**>(&moduleinfo)));
  if(err) {
    loaderClose(dlh);
    return err;
  }

  if(!moduleinfo) {
    loaderClose(dlh);
    return "could not find XPLC_Module entry point";
  }

  if(moduleinfo->magic != XPLC_MODULE_MAGIC) {
    loaderClose(dlh);
    return "module has wrong magic";
  }

  switch(moduleinfo->version_major) {
#ifdef UNSTABLE
  case -1:
    /* nothing to do */
    break;
#endif
  default:
    loaderClose(dlh);
    return "unsupported module major version";
  };

  if(moduleinfo->loadModule && !moduleinfo->loadModule()) {
    loaderClose(dlh);
    return "cannot load module";
  }

  info = moduleinfo;

  return 0;
}

