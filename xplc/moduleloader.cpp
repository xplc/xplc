/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Net Integration Technologies, Inc.
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

#include <stdio.h>
#include <dirent.h>
#include <xplc/xplc.h>
#include <xplc/module.h>
#include <xplc/utils.h>
#include "loader.h"
#include "moduleloader.h"

IObject* ModuleLoader::create() {
  return new GenericComponent<ModuleLoader>;
}

ModuleLoader::~ModuleLoader() {
  shutdown();
}

IObject* ModuleLoader::getInterface(const UUID& aUuid) {
  if(aUuid.equals(IObject::IID)) {
    addRef();
    return static_cast<IObject*>(this);
  }

  if(aUuid.equals(IServiceHandler::IID)) {
    addRef();
    return static_cast<IServiceHandler*>(this);
  }

  if(aUuid.equals(IModuleLoader::IID)) {
    addRef();
    return static_cast<IModuleLoader*>(this);
  }

  return 0;
}

IObject* ModuleLoader::getObject(const UUID& uuid)
{
  ModuleList* module = modules;
  IObject* obj = 0;

  while(module) {
    if(module->module)
      obj = module->module->getObject(uuid);

    if(obj)
      return obj;
  }

  return 0;
}

void ModuleLoader::shutdown()
{
  ModuleList* next;

  while(modules) {
    loaderClose(modules->dlh);
    next = modules->next;
    delete modules;
    modules = next;
  }
}

void ModuleLoader::setModuleDirectory(const char* directory)
{
  DIR* dir;
  struct dirent* ent;
  const size_t len = strlen(directory) + 256 + 1;
  char* fname;
  IServiceManager* servmgr;

  dir = opendir(directory);
  if(!dir)
    return;

  fname = static_cast<char*>(malloc(len));
  servmgr = XPLC::getServiceManager();

  rewinddir(dir);
  while((ent = readdir(dir)) && fname && servmgr) {
    const char* err;
    void* dlh;
    XPLC_GetModuleFunc getmodule = 0;
    IModule* module;
    ModuleList* newmodule;

    snprintf(fname, len, "%s/%s", directory, ent->d_name);

    err = loaderOpen(fname, &dlh);
    if(err)
      continue;

    err = loaderSymbol(dlh, "XPLC_GetModule",
		       reinterpret_cast<void**>(&getmodule));
    if(err || !getmodule) {
      loaderClose(dlh);
      continue;
    }

    module = getmodule(servmgr, XPLC_MODULE_VERSION);
    if(!module) {
      loaderClose(dlh);
      continue;
    }

    newmodule = new ModuleList(module, dlh, modules);
    if(newmodule)
      modules = newmodule;
  }

  if(servmgr)
    servmgr->release();

  free(fname);

  closedir(dir);
}

