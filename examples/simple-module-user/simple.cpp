/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#include <stdio.h>
#include <xplc/xplc.h>
#include "IExample.h"
#include "simple.h"

/*
 * This is an helper class from the C++ binding. While it is not XPLC
 * itself (despite the name), it makes XPLC itself easier to use in
 * C++.
 *
 * It should live at least as long as you intend to use XPLC, as it
 * keeps it alive.
 *
 * Although this wastes a tiny bit of space, it is allowed to have
 * more than one XPLC helper object in a single process, since XPLC
 * uses reference counting. This is useful for libraries, which can
 * create their own XPLC helper object, and if the main application
 * also uses XPLC, or if another library used by the application uses
 * XPLC (even if the application doesn't!), they will be able to
 * cooperate through XPLC.
 */
XPLC xplc;

int main() {
  xplc.addModuleDirectory("../simple-module");

  xplc_ptr<IExample> example(xplc.get<IExample>(SimpleComponent_CID));

  if (example) {
    example->sayHello();
  } else {
    printf("SimpleComponent not found\n");
  }

  return 0;
}

