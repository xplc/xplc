/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002-2004, Net Integration Technologies, Inc.
 * Copyright (C) 2002-2004, Pierre Phaneuf
 * Copyright (C) 2002-2004, Stéphane Lajoie
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"

#if !defined(WIN32)
# if HAVE_DIRENT_H
#  include <dirent.h>
#  define NAMLEN(dirent) strlen((dirent)->d_name)
# else
#  define dirent direct
#  define NAMLEN(dirent) (dirent)->d_namlen
#  if HAVE_SYS_NDIR_H
#   include <sys/ndir.h>
#  endif
#  if HAVE_SYS_DIR_H
#   include <sys/dir.h>
#  endif
#  if HAVE_NDIR_H
#   include <ndir.h>
#  endif
# endif
#else
# include <io.h>
#endif

#include <xplc/core.h>
#include <xplc/module.h>
#include <xplc/utils.h>
#include "loader.h"
#include "moduleloader.h"

UUID_MAP_BEGIN(ModuleLoader)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_ENTRY(IModuleLoader)
  UUID_MAP_END

struct ModuleNode {
  ModuleNode* next;
  const XPLC_ModuleInfo* info;
  void* dlh;
  ModuleNode(const XPLC_ModuleInfo* aInfo, void* aDlh, ModuleNode* aNext):
    next(aNext), info(aInfo), dlh(aDlh) {
  }
  ~ModuleNode() {
    if(dlh)
      loaderClose(dlh);
  }
};

IObject* getModuleObject(const XPLC_ComponentEntry* components,
                         const UUID& uuid) {
  IObject* obj = 0;

  if(components) {
    const XPLC_ComponentEntry* entry = components;

    while(!obj && entry->uuid != UUID_null) {
      if(entry->uuid == uuid)
        obj = entry->getObject();

      ++entry;
    }
  }
    
  return obj;
}

ModuleLoader::~ModuleLoader() {
  ModuleNode* next;
  void* dlh;

  while(modules) {
    dlh = modules->dlh;
    next = modules->next;
    delete modules;
    modules = next;
  }
}

IObject* ModuleLoader::getObject(const UUID& uuid)
{
  ModuleNode* node = modules;

  while(node) {
    IObject* obj = getModuleObject(node->info->components, uuid);

    if(obj)
      return obj;

    node = node->next;
  }

  return 0;
}

void ModuleLoader::loadModule(const char* fname)
{
  XPLC_ModuleInfo* moduleinfo = 0;
  ModuleNode* newmodule;
  void* dlh;
  const char* err;

  err = loaderOpen(fname, &dlh);
  if(err)
    return;

  err = loaderSymbol(dlh, "XPLC_Module",
                     reinterpret_cast<void**>(&moduleinfo));
  if(err
     || !moduleinfo
     || moduleinfo->magic != XPLC_MODULE_MAGIC) {
    loaderClose(dlh);
    return;
  }

  switch(moduleinfo->version_major) {
#ifdef UNSTABLE
  case -1:
    /* nothing to do */
    break;
#endif
  default:
    loaderClose(dlh);
    return;
  };

  if(moduleinfo->loadModule && !moduleinfo->loadModule()) {
    loaderClose(dlh);
    return;
  }

  newmodule = new ModuleNode(moduleinfo, dlh, modules);
  if(newmodule)
    modules = newmodule;
}

#if !defined(WIN32)
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
  servmgr = XPLC_getServiceManager();

  rewinddir(dir);
  while((ent = readdir(dir)) && fname && servmgr) {
    snprintf(fname, len, "%s/%s", directory, ent->d_name);

    loadModule(fname);
  }

  if(servmgr)
    servmgr->release();

  free(fname);

  closedir(dir);
}

#elif defined(WIN32)

void ModuleLoader::setModuleDirectory(const char* directory)
{
  const size_t len = strlen(directory) + 256 + 1;
  char pattern[1024];
  strcpy(pattern, directory);
  strcat(pattern, "/*.*");

  _finddata_t data;
  intptr_t dir = _findfirst(pattern, &data);

  if(!dir)
    return;

  char* fname;
  IServiceManager* servmgr;

  fname = static_cast<char*>(malloc(len));
  servmgr = XPLC_getServiceManager();

  bool first = true;
  while(fname && servmgr) {
	if(!first && _findnext(dir, &data))
      break;
    first = false;

    _snprintf(fname, len, "%s/%s", directory, data.name);

    loadModule(fname);
  }

  if(servmgr)
    servmgr->release();

  free(fname);

  _findclose(dir);
}

#endif
