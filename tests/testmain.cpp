/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#include <cstdio>
#include <cstdlib>
#include "test.h"

static unsigned int passed;
static unsigned int failed;
static char* prog;

void test_assert(const char* file,
                 unsigned int line,
                 bool test,
                 const char* reason) {
  if(test) {
    passed++;
  } else {
    failed++;
    fprintf(stderr, "%s:%i: %s\n", file, line, reason);
    fprintf(stderr, "%s: %i failed, %i passed\n", prog, failed, passed);
    exit(1);
  }
}

void test_verify(const char* file,
                 unsigned int line,
                 bool test,
                 const char* reason) {
  if(test) {
    passed++;
  } else {
    failed++;
    fprintf(stderr, "%s:%i: %s\n", file, line, reason);
  }
}

int main(int argc, char* argv[]) {
  passed = 0;
  failed = 0;
  prog = argv[0];

  test000();
  test001();
  test002();
  test003();
  test004();
  test005();
  test006();
  test007();
  test008();
  test009();
  test010();

  if((failed + passed) == 0) {
    fprintf(stderr, "%s: BAD TEST\n", prog);
    exit(1);
  }

  fprintf(stderr, "%s: %i failed, %i passed\n", prog, failed, passed);

  return (failed != 0);
}

