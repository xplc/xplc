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

#include <stddef.h>
#include <xplc/utils.h>
#include "testobj.h"

/*
 * testobj
 *
 * Contains a small test object.
 */

class TestComponent: public ITestComponent {
public:
  static TestComponent* create();
  /* IObject */
  virtual IObject* getInterface(const UUID&);
  /* ITestComponent */
  virtual int getAnswer();
};

inline TestComponent* TestComponent::create() {
  return new GenericComponent<TestComponent>;
}

IObject* TestComponent::getInterface(const UUID& aUuid) {
  if(aUuid.equals(IObject::IID)) {
    addRef();
    return static_cast<IObject*>(this);
  }

  if(aUuid.equals(ITestComponent::IID)) {
    addRef();
    return static_cast<ITestComponent*>(this);
  }

  return 0;
}

int TestComponent::getAnswer() {
  /*
   * The Answer to Life, Universe and Everything.
   */
  return 42;
}

extern "C"
#ifdef WIN32
__declspec(dllexport)
#endif
IObject* XPLC_SimpleModule() {
  return TestComponent::create();
}
