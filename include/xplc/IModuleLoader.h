/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_IMODULELOADER_H__
#define __XPLC_IMODULELOADER_H__

#include <xplc/IServiceHandler.h>

class IModuleLoader: public IServiceHandler { UNSTABLE_INTERFACE
public:
  static const UUID IID;
  virtual void setModuleDirectory(const char* directory) = 0;
};

DEFINE_UUID(IModuleLoader::IID) = {0xd482c148, 0x6cc0, 0x4e57,
				   {0x90, 0x49, 0x7d, 0xbc,
				    0xa1, 0x47, 0x79, 0xb6}};

#endif /* __XPLC_IMODULELOADER_H__ */
