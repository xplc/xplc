/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
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

#ifndef __XPLC_ICATEGORYENTRY_H__
#define __XPLC_ICATEGORYENTRY_H__

#include <xplc/IObject.h>

/** \interface ICategoryEntry ICategoryEntry.h xplc/ICategoryEntry.h
 *
 * Represents a member of a given category.
 */

class ICategoryEntry: public IObject {
  UNSTABLE_INTERFACE
public:
  /** Returns the UUID of the category entry. */
  virtual const UUID& getUuid() = 0;
};

DEFINE_IID(ICategoryEntry, {0x97dbdd09, 0x8814, 0x4262,
  {0xa5, 0x90, 0x06, 0x7a, 0xdf, 0x83, 0x8a, 0x6c}});

#endif /* __XPLC_ICATEGORYENTRY_H__ */
