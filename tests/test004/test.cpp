/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
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

#include "../test.h"
#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "../../xplc/factory.h"

/*
 * test004
 *
 * Verifies the generic factory.
 */

IObject* testfactory() {
  return new TestObject;
}

void test() {
  IGenericFactory* factory;
  IObject* obj;
  ITestInterface* test;

  obj = GenericFactory::create();
  ASSERT(obj, "could not instantiate generic factory");

  obj->addRef();

  factory = mutateInterface<IGenericFactory>(obj);
  ASSERT(factory, "factory does not have expected interface");

  factory->setFactory(testfactory);

  obj = factory->createObject();
  ASSERT(obj, "factory did not create test object");

  test = mutateInterface<ITestInterface>(obj);
  ASSERT(test, "test object does not have expected interface");

  VERIFY(test->release() == 0, "test object has non-zero refcount after release");

  VERIFY(factory->release() == 0, "factory has non-zero refcount after release");
}

