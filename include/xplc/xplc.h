/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
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

#ifndef __XPLC_XPLC_H__
#define __XPLC_XPLC_H__

#include <xplc/IServiceManager.h>

class XPLC {
public:
  /*
   * Global methods
   */
  static IServiceManager* getServiceManager();
  /*
   * XPLC components
   */
  static const UUID staticServiceHandler;
  static const UUID simpleDynamicLoader;
  static const UUID genericFactory;
  static const UUID monikers;
  static const UUID newMoniker;
};

DEFINE_UUID(XPLC::staticServiceHandler) = {0xf8c76062, 0xf241, 0x4f38,
                                           {0x80, 0x8d, 0x73, 0x88,
                                            0x31, 0x22, 0x89, 0xd8}};

DEFINE_UUID(XPLC::simpleDynamicLoader) = {0xc8c4d2c6, 0x76b8, 0x4f86,
                                          {0x90, 0x7d, 0x05, 0x42,
                                           0x9b, 0xc8, 0x62, 0xe8}};

DEFINE_UUID(XPLC::genericFactory) = {0x414a69c6, 0x3c9e, 0x49f7,
                                     {0xab, 0x08, 0xe5, 0x5c,
                                      0x7b, 0x6c, 0x23, 0x34}};

DEFINE_UUID(XPLC::monikers) = {0x5ed8cb8f, 0x6938, 0x40f2,
                               {0x92, 0x7c, 0x2f, 0x4c,
                                0xe2, 0x89, 0x3c, 0x0b}};

DEFINE_UUID(XPLC::newMoniker) = {0x9ec8028c, 0x45e3, 0x40ff,
                                 {0x97, 0xfc, 0x0b, 0x35,
                                  0xca, 0x6e, 0xdc, 0xb5}};

#endif /* __XPLC_XPLC_H__ */
