/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
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

#include <stddef.h>
#include <xplc/utils.h>
#include <xplc/module.h>
#include "testobj.h"

/*
 * testobj
 *
 * Contains a small test object.
 */

class TestComponent: public ITestComponent {
  IMPLEMENT_IOBJECT(TestComponent);
public:
  static TestComponent* create();
  /* ITestComponent */
  virtual int getAnswer();
};

TestComponent* TestComponent::create() {
  return new TestComponent;
}

int TestComponent::getAnswer() {
  /*
   * The Answer to Life, Universe and Everything.
   */
  return 42;
}

static IObject* factory() {
  static TestComponent* component = 0;

  if(!component)
    component = TestComponent::create();

  if(component)
    component->addRef();

  return component;
}

UUID_MAP_BEGIN(TestComponent)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(ITestComponent)
  UUID_MAP_END

const XPLC_ComponentEntry components[] = {
  { TestComponent_CID, &factory },
  { UUID_null, 0 }
};

const XPLC_ModuleInfo XPLC_Module = {
  XPLC_MODULE_MAGIC,
  XPLC_MODULE_VERSION_MAJOR,
  XPLC_MODULE_VERSION_MINOR,
  "Test Module",
  components,
  0,
  0
};

