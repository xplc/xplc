/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002-2004, Net Integration Technologies, Inc.
 * Copyright (C) 2002-2003, Pierre Phaneuf
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

#ifndef __XPLC_MODULELOADER_H__
#define __XPLC_MODULELOADER_H__

#include <xplc/IModule.h>
#include <xplc/IModuleLoader.h>
#include <xplc/module.h>

IObject* getModuleObject(const XPLC_ComponentEntry*, const UUID&);

struct ModuleNode;

class ModuleLoader: public IModuleLoader {
  IMPLEMENT_IOBJECT(ModuleLoader);
private:
  ModuleNode* modules;
  void loadModule(const char*);
protected:
  ModuleLoader():
    modules(0) {
  }
  virtual ~ModuleLoader();
public:
  static IObject* create() {
    return new ModuleLoader;
  }
  /* IServiceHandler */
  virtual IObject* getObject(const UUID&);
  /* IModuleLoader */
  virtual void setModuleDirectory(const char* directory);
};

#endif /* __XPLC_MODULELOADER_H__ */
