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

#include <dlfcn.h>
#include "loader.h"

const char* loaderOpen(const char* aFilename,
		       void** aHandle) {
  const char* rv = 0;

  /* clear out dl error */
  static_cast<void>(dlerror());
  
  *aHandle = dlopen(aFilename, RTLD_NOW);

  if(!*aHandle)
    rv = dlerror();

  return rv;
}

const char* loaderSymbol(void* aHandle,
			 const char* aSymbol,
			 void** aPointer) {
  /* clear out dl error */
  static_cast<void>(dlerror());

  *aPointer = dlsym(aHandle, aSymbol);

  return dlerror();
}

bool loaderClose(void* aHandle) {
  return dlclose(aHandle) == 0;
}

