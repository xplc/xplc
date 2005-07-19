/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#include <xplc/module.h>
#include "module.h"

/* This is the list of UUIDs that this module can provide objects for,
 * along with a pointer to the function that will provide it. This *
 * example has only one component, but there is no restriction on how
 * many components can a single module have (you do not have to put
 * one component per module).
*/
static const XPLC_ComponentEntry components[] = {
  { SimpleComponent_CID, &getSimpleComponent },
  { UUID_null, 0 }
};

const XPLC_ModuleInfo XPLC_Module = {
  XPLC_MODULE_MAGIC,
  XPLC_MODULE_VERSION_MAJOR,
  XPLC_MODULE_VERSION_MINOR,
  "Simple Example Module",
  components,
  0
};

