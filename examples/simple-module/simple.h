/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#ifndef __EXAMPLE_SIMPLE_H__
#define __EXAMPLE_SIMPLE_H__

/*
 * This file should be available to client code.
 *
 * This is a "well-known" UUID that is used to get the component. We
 * say "well-known", because the assumption is that client code will
 * already know this, somehow (by including this file, for example).
 *
 * The "CID" suffix stands for "Component ID". This is a normal UUID,
 * there is nothing different except the name, but it helps to have
 * some context when discussing or documenting things.
 */

static const UUID SimpleComponent_CID = {0x71c4067f, 0xaaa4, 0x4e6c, {0xa7, 0x07, 0x14, 0x38, 0xeb, 0x04, 0xb0, 0x7d}};

#endif /* __EXAMPLE_SIMPLE_H__ */
