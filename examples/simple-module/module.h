/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#ifndef __EXAMPLE_MODULE_H__
#define __EXAMPLE_MODULE_H__

#include "simple.h"

/*
 * This is private to the module.
 *
 * The content of this file is completely internal to the module, it
 * is only used to share this prototype between simple.cpp and
 * module.cpp. Client code using this component do not need this file
 * at all.
 */

IObject* getSimpleComponent();

#endif /* __EXAMPLE_MODULE_H__ */
