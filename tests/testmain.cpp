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
#include <cassert>
#include <cstring>
#include "test.h"

static unsigned int passed;
static unsigned int failed;

struct Test {
  const char* name;
  void (*test)();
};

static char* prog;

#define ADD_TEST(testname) { #testname, testname }

static Test tests[] = {
  ADD_TEST(test000),
  ADD_TEST(test001),
  ADD_TEST(test002),
  ADD_TEST(test003),
  ADD_TEST(test004),
  ADD_TEST(test005),
  ADD_TEST(test006),
  ADD_TEST(test007),
  ADD_TEST(test008),
  ADD_TEST(test009),
  ADD_TEST(test010),
  ADD_TEST(test011),
  { 0, 0 }
};

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
  Test* test = tests;
  unsigned int total_passed = 0;
  unsigned int total_failed = 0;
  prog = argv[0];

  for(test = tests; test && test->test; ++test) {
    assert(test->name);

    if(argc > 1) {
      int argsleft = argc;

      for(argsleft = argc;
          argsleft > 1 && strcmp(argv[argsleft - 1], test->name) != 0;
          --argsleft) {
      }

      if(argsleft <= 1)
        continue;
    }

    passed = 0;
    failed = 0;
    test->test();
    total_passed += passed;
    total_failed += failed;
  }

  if((total_failed + total_passed) == 0) {
    fprintf(stderr, "%s: BAD TEST\n", prog);
    exit(1);
  }

  fprintf(stderr, "%s: %i failed, %i passed\n",
          prog, total_failed, total_passed);

  return (total_failed != 0);
}

