/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_TRACE_H__
#define __XPLC_TRACE_H__

#ifdef DEBUG

#include <stdio.h>

/*
 * Mix-in template that trace constructors, destructors and refcount
 * to stderr.
 */
template<class Component>
class TraceComponent: public Component {
public:
  TraceComponent() {
    fprintf(stderr, "%s: instantiated (%p)\n", __PRETTY_FUNCTION__, this);
  }
  virtual unsigned int addRef() {
    unsigned int refcount = Component::addRef();

    fprintf(stderr, "%s = %i (%p)\n", __PRETTY_FUNCTION__, refcount, this);

    return refcount;
  }
  virtual unsigned int release() {
    unsigned int refcount = Component::release();

    fprintf(stderr, "%s = %i (%p)\n", __PRETTY_FUNCTION__, refcount, this);

    return refcount;
  }
  virtual ~TraceComponent() {
    fprintf(stderr, "%s: destroyed (%p)\n", __PRETTY_FUNCTION__, this);
  }
};

#else /* DEBUG */

#error "this header should not be used other than for debugging"

#endif /* else DEBUG */

#endif /* __XPLC_TRACE_H__ */
