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

#ifndef __XPLC_ISINGLEMODULELOADER_H__
#define __XPLC_ISINGLEMODULELOADER_H__

#include <xplc/IServiceHandler.h>

class ISingleModuleLoader: public IServiceHandler { UNSTABLE_INTERFACE
public:
  static const UUID IID;
  /*
   * Loading a library while the component already has another library
   * open will result in the first library to be unloaded. Returns
   * error message on error, or NULL if the module was loaded
   * successfully.
   */
  virtual const char* loadModule(const char* filename) = 0;
};

DEFINE_UUID(ISingleModuleLoader::IID) = {0x0f8eb75a, 0x0b47, 0x494f,
                                         {0xb2, 0xa8, 0x7b, 0x2f,
                                          0xb0, 0xef, 0x99, 0xde}};

#endif /* __XPLC_ISINGLEMODULELOADER_H__ */
