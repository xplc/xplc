/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 * Copyright (C) 2002, Stéphane Lajoie
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

#ifndef __XPLC_IOBJECT_H__
#define __XPLC_IOBJECT_H__

#include <xplc/uuid.h>

#ifndef UNSTABLE
#define UNSTABLE_INTERFACE static bool UNSTABLE_INTERFACE = true;
#else
#define UNSTABLE_INTERFACE
#endif

class IObject { UNSTABLE_INTERFACE
public:
  static const UUID IID;
  virtual unsigned int addRef() = 0;
  virtual unsigned int release() = 0;
  virtual IObject* getInterface(const UUID&) = 0;
};

DEFINE_UUID(IObject::IID) = {0x8ca76e98, 0xb653, 0x43d7,
                             {0xb0, 0x56, 0x8b, 0x9d,
                              0xde, 0x9a, 0xbe, 0x9d}};

#endif /* __XPLC_IOBJECT_H__ */
