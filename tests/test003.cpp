/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
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

#include "test.h"
#include <xplc/utils.h>
#include <xplc/factory.h>

/*
 * test003
 *
 * Verifies the generic factory.
 */

IObject* testfactory() {
  return new TestObject;
}

void test003() {
  IFactory* factory;
  IObject* obj;
  ITestInterface* test;

  obj = new GenericFactory(testfactory);
  ASSERT(obj != 0, "could not instantiate generic factory");

  factory = mutate<IFactory>(obj);
  ASSERT(factory != 0, "factory does not have expected interface");

  obj = factory->createObject();
  ASSERT(obj != 0, "factory did not create test object");

  test = mutate<ITestInterface>(obj);
  ASSERT(test != 0, "test object does not have expected interface");

  VERIFY(test->release() == 0, "test object has non-zero refcount after release");

  VERIFY(factory->release() == 0, "factory has non-zero refcount after release");

  delete test;
}

