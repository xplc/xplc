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

#ifndef __XPLC_IOBJECT_H__
#define __XPLC_IOBJECT_H__

#include <xplc/uuid.h>

class IObject {
protected:
  /*
   * FIXME: This is so that only the component itself can "delete"
   * itself, preventing user code from invoking delete on an interface
   * (which is forbidden). But I am not sure if this will work
   * everywhere (Visual C++ is rather braindead). A protected
   * destructor works, but generates spurious warnings about it not
   * being virtual, and making it virtual would change the layout of
   * the virtual method table, which must not happen.
   */
  void operator delete(void* ptr) {
    ::operator delete(ptr);
  }
public:
  static const UUID IID;
  virtual unsigned int addRef() = 0;
  virtual unsigned int release() = 0;
  virtual IObject* getInterface(const UUID&) = 0;
};

DEFINE_IID(IObject::IID) = {0x8ca76e98, 0xb653, 0x43d7, {0xb0, 0x56, 0x8b, 0x9d, 0xde, 0x9a, 0xbe, 0x9d}};

#endif /* __XPLC_IOBJECT_H__ */
