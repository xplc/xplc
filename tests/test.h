/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#ifndef __TESTS_TEST_H__
#define __TESTS_TEST_H__

#include <xplc/core.h>
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

class ITestInterface: public IObject {
public:
  virtual unsigned int getRefCount() = 0;
  virtual void setRefCount(unsigned int) = 0;
};

DEFINE_IID(ITestInterface, {0x794e20af, 0x5d35, 0x4d7a,
  {0x8f, 0x23, 0xf8, 0x53, 0xd7, 0x34, 0xb3, 0xa7}});

class TestObject: public ITestInterface {
private:
  unsigned int refcount;
  bool destroyed;
  bool deletethis;
public:
  TestObject(const bool _deletethis = false): refcount(0), destroyed(false),
                                      deletethis(_deletethis) {
  }
  virtual ~TestObject() {
  }
  void operator delete(void* self) {
    ::operator delete(self);
  }
  virtual unsigned int addRef() {
    ASSERT(!destroyed, "test object destroyed more than once");

    return ++refcount;
  }
  virtual unsigned int release() {
    ASSERT(!destroyed, "using destroyed test object");

    if(--refcount)
      return refcount;

    refcount = 1;
    destroyed = true;
    if(deletethis)
      delete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    ASSERT(!destroyed, "using destroyed test object");

    if(uuid.equals(IID<IObject>::get())) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid.equals(IID<ITestInterface>::get())) {
      addRef();
      return static_cast<ITestInterface*>(this);
    }

    return 0;
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
public:
  TestObjectFactory(): refcount(0), destroyed(false) {
  }
  virtual ~TestObjectFactory() {
  }
  void operator delete(void* self) {
    ::operator delete(self);
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

    delete this;

    return 0;
  }
  virtual IObject* getInterface(const UUID& uuid) {
    if(uuid.equals(IID<IObject>::get())) {
      addRef();
      return static_cast<IObject*>(this);
    }

    if(uuid.equals(IID<IFactory>::get())) {
      addRef();
      return static_cast<IFactory*>(this);
    }

    return 0;
  }
  virtual IObject* createObject() {
    IObject* obj = new TestObject(true);

    if(obj)
      obj->addRef();

    return obj;
  }
};

static const UUID TestObjectFactory_CID = {0x9cacf26d, 0xd362, 0x4543, {0xb0, 0x42, 0x10, 0xe8, 0xcb, 0xa3, 0xfd, 0xab}};

#endif /* __TESTS_TEST_H__ */
