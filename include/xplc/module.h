/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_MODULE_H__
#define __XPLC_MODULE_H__

#include <xplc/IModule.h>
#include <xplc/IServiceManager.h>

#ifdef WIN32
#define ENTRYPOINT __declspec(dllexport) extern "C"
#else
#define ENTRYPOINT extern "C"
#endif

/*
 * The IModule returned by XPLC_GetModule should be already addRef'd.
 */

ENTRYPOINT IModule* XPLC_GetModule(IServiceManager*,
				   const unsigned int);

typedef IModule*(*XPLC_GetModuleFunc)(IServiceManager*,
				      const unsigned int);

#define XPLC_MODULE_VERSION 0

#endif /* __XPLC_MODULE_H__ */
