/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2004, Pierre Phaneuf
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
#include <xplc/ptr.h>

/*
 * test011
 *
 * Tests xplc_ptr<>.
 */

void test011() {
  TestObject* testobj1 = new TestObject(false);
  TestObject* testobj2 = new TestObject(false);
  IObject* obj;
  ITestInterface* testiface;
  ITestInterface2* testiface2;

  testobj1->addRef();
  testobj2->addRef();

  {
    xplc_ptr<ITestInterface2> ptr1(testobj1);
    xplc_ptr<ITestInterface2> ptr2(testobj2);
    xplc_ptr<ITestInterface> ptr3(ptr1);

    VERIFY(ptr1->getRefCount() == 3, "incorrect refcount on test object 1");
    VERIFY(ptr2->getRefCount() == 2, "incorrect refcount on test object 2");

    VERIFY(ptr1, "test for truth");
    VERIFY(!(!ptr1), "test for falseness");
    VERIFY(ptr1 == ptr1, "test for self-equality");

    VERIFY(!(ptr1 == ptr2), "test for broken equality");
    VERIFY(ptr1 != ptr2, "test for broken non-equality");

    if(testobj1 < testobj2) {
      VERIFY(ptr1 < ptr2, "test for less-than operator");
      VERIFY(!(ptr2 < ptr1), "test for less-than operator");
      VERIFY(ptr2 > ptr1, "test for greater-than operator");
      VERIFY(!(ptr1 > ptr2), "test for greater-than operator");
    } else {
      VERIFY(ptr2 < ptr1, "test for less-than operator");
      VERIFY(!(ptr1 < ptr2), "test for less-than operator");
      VERIFY(ptr1 > ptr2, "test for greater-than operator");
      VERIFY(!(ptr2 > ptr1), "test for greater-than operator");
    }

    ptr1 = 0;

    VERIFY(testobj1->getRefCount() == 2, "incorrect refcount on test object");

    ptr1 = testobj1;

    obj = ptr1;
    VERIFY(obj == testobj1, "assignment to IObject");

    testiface = ptr1;
    VERIFY(testiface == testobj1, "assignment to ITestInterface");

    testiface2 = ptr1;
    VERIFY(testiface2 == testobj1, "assignment to ITestInterface2");

    VERIFY(testobj1->getRefCount() == 3, "incorrect refcount on test object 1");
  }

  VERIFY(testobj1->release() == 0, "incorrect refcount on test object 1");
  VERIFY(testobj2->release() == 0, "incorrect refcount on test object 2");

  delete testobj1;
  delete testobj2;
}
