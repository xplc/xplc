/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
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

#ifndef __XPLC_UUID_H__
#define __XPLC_UUID_H__

/** \file
 *
 * Definitions related to UUIDs.
 */

/**
 * A Universally Unique IDentifier.
 * 
 * This is a sequence of 16 bytes that is unique throughout the
 * universe, and which can uniquely identify anything you might want.
 * It will never have a name conflict with any other UUID.  To come up
 * with a UUID of your own, run the 'uuidgen' program that comes with
 * many Unix and Windows systems.  Although any UUID is guaranteed to
 * be unique, there is a downside: it's almost impossible for a human
 * to read, understand, or remember the contents of a UUID.  For a
 * less unique, human-readable alternative to UUIDs, see IMoniker.
 * 
 * A UUID is what is known as a "strong name". It is like the name of
 * a class in a C++ program, or of a global variable, but the "strong"
 * part refers to how this name, unlike the name of a C++ class, is
 * unique and refers precisely to this one thing. C++ names are "weak
 * names", it is very easy to create two different things with the
 * same name, for example, classes named "String" are very common, and
 * two different "String" classes could not be used in the same
 * program. When making a single program, it is possible to avoid
 * these conflicts, but with a component system, you never know how
 * components will be used together, thus the need for strong names.
 *
 * The UUID is the standard way of looking up and indexing objects in
 * XPLC.  All "well-known" objects you need to look for (such as the
 * standard XPLC moniker and category services, and other objects you
 * create yourself) will have a UUID you can look up using the service
 * manager.  Note that objects referenced by a UUID are necessarily
 * "singletons" - that is, objects of a class that is only
 * instantiated once in any program.  For example, a factory that
 * produces HelloWorld objects would have its own UUID - so you can
 * ask for a HelloWorldFactory and get "the" HelloWorldFactory - but
 * the HelloWorld objects it produces would not be findable by UUID.
 * (If they all had the same UUID, it wouldn't be very Universally
 * Unique, would it?  And if they all had different UUIDs, how would
 * you know which UUID to look for?)
 * 
 * Also: when you retrieve a different interface from an IObject using
 * its getInterface() method, you do so by looking up the UUID of that
 * interface, also known as an IID (which is just a nickname for UUID,
 * they are identical in meaning).  Every interface must have an IID,
 * but the IID is the same for all objects implementing that
 * interface.  However, you can have multiple objects implementing a
 * particular interface, and each of those objects will have its own
 * UUID.
 */
struct UUID {
  /* FIXME: the sizes of these objects are not the same on all platforms! */
  //@{
  unsigned int data0;
  unsigned short data1;
  unsigned short data2;
  unsigned char data3[8];
  //@}

  /* FIXME: the remaining of this is C++-specific. */
    
  /// Return true if this object equals the given UUID.
  bool equals(const UUID& uuid) const {
    return
      (this == &uuid) ||
      ((static_cast<const unsigned int*>(&data0)[0] == static_cast<const unsigned int*>(&uuid.data0)[0]) &&
       (static_cast<const unsigned int*>(&data0)[1] == static_cast<const unsigned int*>(&uuid.data0)[1]) &&
       (static_cast<const unsigned int*>(&data0)[2] == static_cast<const unsigned int*>(&uuid.data0)[2]) &&
       (static_cast<const unsigned int*>(&data0)[3] == static_cast<const unsigned int*>(&uuid.data0)[3]));
  }
    
  /**
   * Fill the contents of this UUID using a printable C string.  The string
   * is of the form: 9c318f06-52ec-4a62-b5fb-9279216e8586
   * 
   * This is the form produced by the 'uuidgen' program and is used in the
   * Windows registry.
   */
  void fromString(const char* str);
  
  /**
   * Fill the given pointer with a printable string representing this UUID.
   * The string is of the form: 9c318f06-52ec-4a62-b5fb-9279216e8586
   * 
   * 'str' should point to at least 39 bytes of available memory.
   * Always returns 'str', which has been null-terminated.
   */
  char* toString(char* str) const;
};

/// The NULL UUID.  Nothing will ever have this UUID, I promise.
static const UUID UUID_null = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};

/** \struct IID uuid.h xplc/uuid.h
 *
 * An Interface IDentifier.  Every interface (abstract classes derived from
 * IObject) must have a unique IID, so that getInterface() can ask for that
 * interface.
 * 
 * Generate a UUID for your IID using 'uuidgen', then declare your IID
 * using DEFINE_IID(ClassName).  If you need to obtain the UUID corresponding
 * to that interface in the future, call the static function
 * IID<ClassName>::get().
 */
template<class T>
struct IID {
};

/**
 * Used to define the IID of an interface.
 */
#define DEFINE_IID(iface, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11) \
static const UUID iface##_IID = u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11; \
template <> \
struct IID<iface> { \
  static const UUID& get() { \
    return iface##_IID; \
  } \
}

#endif /* __XPLC_UUID_H__ */
