/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002-2003, Pierre Phaneuf
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

#include "test.h"
#include <stdio.h>
#include <string.h>

/*
 * test007
 *
 * Verifies the UUID stringification and parsing.
 */

#ifdef WIN32
#define snprintf _snprintf
#endif

void test007() {
  const UUID u0 = {0xe87db3a0, 0x109a, 0x4ecb, {0x86, 0x64, 0x66, 0x85,
						0x45, 0x20, 0xa6, 0xcc}};
  UUID u1;
  const char u2[] = "e87db3a0-109a-4ecb-8664-66854520a6cc";
  char u3[39];
  char u4[39];
  char u5[39];
  char u6[38];
  int rv;

  ASSERT(sizeof(u0) == 16, "UUID structure is of unexpected size");

  ASSERT(sizeof(u2) == 37, "u2 is of unexpected size");

  u1 = UUID_null;
  u1 = UuidFromString(u2);
  VERIFY(u1 == u0, "u2 was not parsed properly into u1");

  rv = snprintf(u3, 39, "{%s}", u2);
  ASSERT(rv == 38, "copying u2 into u3 with curly braces failed");

  u1 = UUID_null;
  VERIFY(u1 == UUID_null, "u1 is not equal to UUID_null after resetting");

  u1 = UuidFromString(u3);
  VERIFY(u1 == u0, "u3 was not parsed properly into u1");

  rv = snprintf(u4, 39, "{%x-%x-%x-%x%x-%x%x%x%x%x%x}",
		u0.Data1, u0.Data2, u0.Data3,
		u0.Data4[0],
		u0.Data4[1],
		u0.Data4[2],
		u0.Data4[3],
		u0.Data4[4],
		u0.Data4[5],
		u0.Data4[6],
		u0.Data4[7]);
  ASSERT(rv == 38, "formatting u0 into u4 (with snprintf) failed");

  VERIFY(strncmp(u3, u4, 39) == 0, "result of formatting u0 into u4 was different from u3");

  UuidToString(u0, u5);
  VERIFY(strncmp(u3, u5, 39) == 0, "result of using toString on u0 was different from u3");

  rv = snprintf(u6, 38, "{%s", u2);
  ASSERT(rv == 37, "copying u2 into u6 with starting curly brace failed");

  u1 = u0;
  u1 = UuidFromString(u6);
  VERIFY(u1 == UUID_null, "fromString wrongfully accepted u6 into u1");

  rv = snprintf(u6, 38, "%s}", u2);
  ASSERT(rv == 37, "copying u2 into u6 with ending curly brace failed");

  u1 = u0;
  u1 = UuidFromString(u6);
  VERIFY(u1 == UUID_null, "fromString wrongfully accepted u6 into u1");
}

