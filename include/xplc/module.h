/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 * Copyright (C) 2002, Stéphane Lajoie
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

#ifndef __XPLC_MODULE_H__
#define __XPLC_MODULE_H__

/** \file
 *
 * Structures and definitions related to the XPLC module ABI
 * (Application Binary Interface).
 */

#ifdef UNSTABLE
#include <limits.h>
#endif
#include <xplc/IModule.h>

#define XPLC_MODULE_MAGIC 0x58504c43UL

/**
 * The current XPLC module ABI version.
 */
#ifdef UNSTABLE
#define XPLC_MODULE_VERSION_MAJOR UINT_MAX
#define XPLC_MODULE_VERSION_MINOR 0
#else
#define XPLC_MODULE_VERSION_MAJOR 0
#define XPLC_MODULE_VERSION_MINOR 0
#endif

/**
 * Defines attributes required for exported symbols.
 */
#ifdef WIN32
#define ENTRYPOINT extern "C" __declspec(dllexport)
#else
#define ENTRYPOINT extern "C"
#endif

struct XPLC_ComponentEntry {
  const UUID& uuid;
  IObject* (*getObject)();
};

/**
 * Information for an XPLC module.
 */
struct XPLC_ModuleInfo {
  unsigned long magic;
  /**
   * The XPLC module ABI version that this module conforms to. This
   * should always be the first member of the XPLC_ModuleInfo
   * structure, as the meaning of the following members depend on it.
   */
  unsigned int version_major;
  unsigned int version_minor;

  const char* description;

  const XPLC_ComponentEntry* const components;

  bool (*loadModule)();
  bool (*unloadModule)();
};

/**
 * Definition of the XPLC module information structure. This structure
 * should be initialized appropriately in a loadable XPLC module.
 */
ENTRYPOINT const XPLC_ModuleInfo XPLC_Module;

#endif /* __XPLC_MODULE_H__ */
