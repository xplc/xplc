/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_IMONIKERSERVICE_H__
#define __XPLC_IMONIKERSERVICE_H__

#include <xplc/IMoniker.h>

class IMonikerService: public IMoniker {
public:
  static const UUID IID;
  virtual void registerObject(const char*, const UUID&) = 0;
};

DEFINE_UUID(IMonikerService::IID) = {0x0ee2cc09, 0xd7d5, 0x44ee,
				     {0xbc, 0x63, 0xf2, 0xb9,
				      0x03, 0x7d, 0xb9, 0x82}};

#endif /* __XPLC_IMONIKERSERVICE_H__ */
