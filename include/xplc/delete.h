/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2004, Net Integration Technologies, Inc.
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

#ifndef __XPLC_DELETE_H__
#define __XPLC_DELETE_H__

/** \file
 *
 * Include this file right after IObject.h (or instead of) to detect
 * accidental uses of "delete" on an %XPLC interface. Use "xplcdelete"
 * instead of "delete" when you know what you are doing.
 */

#include <xplc/IObject.h>

class CheckIObject {};
class CheckIObjectOk {};

template<class T>
class ConversionIObject
{
public:
  typedef char Yes;
  struct No { char dummy[2]; };
  static T* from;
  static Yes test(const IObject*);
  static No test(...);
};

template<bool>
struct XPLC_CTAssert;
template<>
struct XPLC_CTAssert<true> {};

template<class T>
inline void operator&&(CheckIObject, const T* obj) {
  static_cast<void>(sizeof(XPLC_CTAssert<(sizeof(ConversionIObject<T>::test(ConversionIObject<T>::from)) != sizeof(typename ConversionIObject<T>::Yes))>));
  delete obj;
}

template<class T>
inline void operator&&(CheckIObjectOk, const T* obj) {
  delete obj;
}

#undef xplcdelete
#define xplcdelete CheckIObjectOk() &&
#define delete CheckIObject() &&

#endif /* __XPLC_DELETE_H__ */
