/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
 * Copyright (C) 2002-2004, Net Integration Technologies, Inc.
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

#ifndef __TESTS_TEST_H__
#define __TESTS_TEST_H__

#include <xplc/core.h>
#include <xplc/IWeakRef.h>
#include <xplc/IFactory.h>

void test000();
void test001();
void test002();
void test003();
void test004();
void test005();
void test006();
void test007();
void test008();
void test009();
void test010();

void test_assert(const char* file,
                 unsigned int line,
                 bool test,
                 const char* reason);

void test_verify(const char* file,
                 unsigned int line,
                 bool test,
                 const char* reason);

#define ASSERT(cond, desc) test_assert(__FILE__, __LINE__, cond, desc)
#define VERIFY(cond, desc) test_verify(__FILE__, __LINE__, cond, desc)

#ifndef xplcdelete
#define xplcdelete delete
#endif

class ITestInterface: public IObject {
public:
  virtual unsigned int getRefCount() = 0;
  virtual void setRefCount(unsigned int) = 0;
};

DEFINE_IID(ITestInterface, {0x794e20af, 0x5d35, 0x4d7a,
  {0x8f, 0x23, 0xf8, 0x53, 0xd7, 0x34, 0xb3, 0xa7}});

class TestWeakRef: public IWeakRef {
private:
  unsigned int refcount;
  bool destroyed;
  TestWeakRef* weakref;
public:
  IObject* object;
  TestWeakRef(IObject* aObject): refcount(1), destroyed(false),
                                 weakref(0), object(aObject) {
  }
  virtual ~TestWeakRef() {
  }
  virtual unsigned int addRef() {
    return ++refcount;
  }
  virtual unsigned int release() {
    if(--refcount)
      return refcount;

    ASSERT(!destroyed, "test object destroyed more than once");

    refcount = 1;
    destroyed = true;

    if(weakref)
      weakref->object = 0;

    xplcdelete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    ASSERT(!destroyed, "using destroyed test object");

    if(uuid == IObject_IID) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid == IWeakRef_IID) {
      addRef();
      return static_cast<IWeakRef*>(this);
    }

    return 0;
  }
  virtual IWeakRef* getWeakRef() {
    if(!weakref) {
      weakref = new TestWeakRef(this);
    }

    return weakref;
  }
  virtual IObject* getObject() {
    if(object)
      object->addRef();

    return object;
  }
};

class TestObject: public ITestInterface {
private:
  unsigned int refcount;
  bool destroyed;
  bool deletethis;
  TestWeakRef* weakref;
public:
  TestObject(const bool _deletethis = false): refcount(1), destroyed(false),
                                      deletethis(_deletethis), weakref(0) {
  }
  virtual ~TestObject() {
  }
  virtual unsigned int addRef() {
    ASSERT(!destroyed, "using destroyed test object");

    return ++refcount;
  }
  virtual unsigned int release() {
    ASSERT(!destroyed, "test object destroyed more than once");

    if(--refcount)
      return refcount;

    refcount = 1;
    destroyed = true;
    if(deletethis)
      xplcdelete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    ASSERT(!destroyed, "using destroyed test object");

    if(uuid == IObject_IID) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid == ITestInterface_IID) {
      addRef();
      return static_cast<ITestInterface*>(this);
    }

    return 0;
  }
  virtual IWeakRef* getWeakRef() {
    if(!weakref) {
      weakref = new TestWeakRef(this);
    }

    return weakref;
  }
  virtual unsigned int getRefCount() {
    ASSERT(!destroyed, "using destroyed test object");

    return refcount;
  }
  virtual void setRefCount(unsigned int aRefCount) {
    ASSERT(!destroyed, "using destroyed test object");

    refcount = aRefCount;

    if(!refcount) {
      refcount = 1;
      destroyed = true;
    }
  }
};

static const UUID TestObject_CID = {0xfa8ebece, 0x047e, 0x4372, {0xb7, 0x34, 0x30, 0x10, 0x05, 0x32, 0x45, 0x47}};

class TestObjectFactory: public IFactory {
private:
  unsigned int refcount;
  bool destroyed;
  TestWeakRef* weakref;
public:
  TestObjectFactory(): refcount(1), destroyed(false), weakref(0) {
  }
  virtual ~TestObjectFactory() {
  }
  virtual unsigned int addRef() {
    return ++refcount;
  }
  virtual unsigned int release() {
    if(--refcount)
      return refcount;

    ASSERT(!destroyed, "test object factory destroyed more than once");

    refcount = 1;
    destroyed = true;

    xplcdelete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid == IObject_IID) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid == IFactory_IID) {
      addRef();
      return static_cast<IFactory*>(this);
    }

    return 0;
  }
  virtual IWeakRef* getWeakRef() {
    if(!weakref) {
      weakref = new TestWeakRef(this);
      weakref->addRef();
    }

    return weakref;
  }
  virtual IObject* createObject() {
    return new TestObject(true);
  }
};

static const UUID TestObjectFactory_CID = {0x9cacf26d, 0xd362, 0x4543, {0xb0, 0x42, 0x10, 0xe8, 0xcb, 0xa3, 0xfd, 0xab}};

#endif /* __TESTS_TEST_H__ */
