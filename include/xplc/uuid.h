/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
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

#ifndef __XPLC_UUID_H__
#define __XPLC_UUID_H__

struct UUID {
  unsigned int data0;
  unsigned short data1;
  unsigned short data2;
  unsigned char data3[8];
  inline bool equals(const UUID& uuid) const {
    return (((unsigned int*)&data0)[0] == ((unsigned int*)&uuid.data0)[0] &&
            ((unsigned int*)&data0)[1] == ((unsigned int*)&uuid.data0)[1] &&
            ((unsigned int*)&data0)[2] == ((unsigned int*)&uuid.data0)[2] &&
            ((unsigned int*)&data0)[3] == ((unsigned int*)&uuid.data0)[3]);
  };
};

#define DEFINE_UUID(symbol) const UUID symbol __attribute__((weak))

#endif /* __XPLC_UUID_H__ */
