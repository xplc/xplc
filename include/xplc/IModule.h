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

#ifndef __XPLC_IMODULE_H__
#define __XPLC_IMODULE_H__

#include <xplc/IObject.h>

class IModule: public IObject { UNSTABLE_INTERFACE
public:
  static const UUID IID;
  /*
   * The object returned by IModule::getObject() is already
   * addRef()'d.
   */
  virtual IObject* getObject(const UUID&) = 0;
};

DEFINE_UUID(IModule::IID) = {0x772689d4, 0x7932, 0x448a, {0x80, 0x8a, 0x6e, 0xbf, 0x1c, 0xe9, 0xf9, 0x4b}};

#endif /* __XPLC_IMODULE_H__ */
