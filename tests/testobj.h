/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
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

#ifndef __TESTS_TEST004_TESTOBJ_H__
#define __TESTS_TEST004_TESTOBJ_H__

#include <xplc/IObject.h>

class ITestComponent: public IObject {
public:
  virtual int getAnswer() = 0;
};

const UUID TestComponent_CID = {0x746d2ba8, 0x0a52, 0x4156, {0xb9, 0x20, 0x05, 0x85, 0x3f, 0xf1, 0x73, 0x43}};

#endif /* __TESTS_TEST004_TESTOBJ_H__ */
