/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#include <stdio.h>
#include <xplc/utils.h>
#include "IExample.h"
#include "simple.h"

class SimpleComponent: public IExample {
  IMPLEMENT_IOBJECT(SimpleComponent);
public:
  virtual void sayHello();
};

UUID_MAP_BEGIN(SimpleComponent)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IExample)
  UUID_MAP_END

IObject* getSimpleComponent() {
  return new SimpleComponent;
}

void SimpleComponent::sayHello() {
  printf("hello from SimpleComponent!\n");
}

