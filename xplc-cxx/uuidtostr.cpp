/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#include <assert.h>
#include <stdio.h>
#include <xplc/uuid.h>

char* UuidToString(const UUID& uuid, char* str) {
  assert(str);

  sprintf(str, "{%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
          uuid.Data1, uuid.Data2, uuid.Data3,
          uuid.Data4[0], uuid.Data4[1], uuid.Data4[2], uuid.Data4[3],
          uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

  return str;
}

