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

#ifndef __XPLC_MODULELOADER_H__
#define __XPLC_MODULELOADER_H__

#include <xplc/IModule.h>
#include <xplc/IModuleLoader.h>

struct ModuleList {
  ModuleList* next;
  IModule* module;
  void* dlh;
  ModuleList(IModule* aModule, void* aDlh, ModuleList* aNext):
    next(aNext), module(aModule), dlh(aDlh) {
  }
  ~ModuleList() {
    module->release();
  }
};

class ModuleLoader: public IModuleLoader {
private:
  ModuleList* modules;
protected:
  ModuleLoader(): modules(0) {
  }
  virtual ~ModuleLoader();
public:
  static IObject* create();
  /* IObject */
  virtual IObject* getInterface(const UUID&);
  /* IServiceHandler */
  virtual IObject* getObject(const UUID&);
  virtual void shutdown();
  /* IModuleLoader */
  virtual void setModuleDirectory(const char* directory);
};

#endif /* __XPLC_MODULELOADER_H__ */
