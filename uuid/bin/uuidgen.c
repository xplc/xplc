/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * uuidgen - UUID generator and preprocessor for XPLC
 * Copyright (C) 2005, Net Integration Technologies, Inc.
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free
 * software library without restriction.  Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU Lesser General Public
 * License.  This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Lesser
 * General Public License.
 */

#include <assert.h>
#include <errno.h>
#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif
#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <uuid/uuid.h>

#include "include/autoconf.h"

#define SOURCE_NONE -1
#define SOURCE_AUTO 0
#define SOURCE_RANDOM 1
#define SOURCE_TIME 2

#define SINK_NONE -1
#define SINK_UUID 0
#define SINK_CDEF 1

struct config_t {
  /* What kind of randomness source do we use? */
  int source;
  /* What kind of output are we generating? */
  int sink;
};

const char* program;		/* Program name */

#define PARSE_INVALID -1
#define PARSE_UNKNOWN 0
#define PARSE_FLAGS 1
#define PARSE_SHORT_OPTIONS 2
#define PARSE_LONG_OPTION 3


void print_help(const char* program) {
  printf("Usage: %s [OPTION]\n", program);
  printf("Generate a new universally unique identifier (UUID)\n");
  printf("\n"
         "  -c, --cdef\toutput C structure for XPLC\n"
         "  -r, --random\tgenerate random-based UUID\n"
         "  -t, --time\tgenerate time-based UUID\n"
         "  -u, --uuid\thuman-readable output\n"
         "      --help\tdisplay this help and exit\n"
         "      --version\toutput version information and exit\n"
         "\n");
  printf("When called without options, this programme will generate a "
         "universally\n"
         "unique identifier (UUID), and output it as requested.\n");
  printf("\n"
         "Report bugs to <" PACKAGE_BUGREPORT ">.\n");
}


void print_version(const char* program) {
  printf("XPLC uuidgen version " PACKAGE_VERSION "\n"
         "Written by Simon Law.\n"
         "\n"
         "Copyright (C) 2005, Net Integration Technologies, Inc.\n"
         "This is free software; see the source for copying conditions.  "
         "There is NO\n"
         "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
         "PARTICULAR PURPOSE.\n");
}


int parse_short_option(const int flag, struct config_t* cfg) {
  if(!cfg) {
    fprintf(stderr,
            "%s: Programmer error at %s:%d\n", program, __FILE__, __LINE__);
    abort();
  }

  switch(flag) {
  case 'c':
    cfg->sink = SINK_CDEF;
    break;
  case 'r':
    cfg->source = SOURCE_RANDOM;
    break;
  case 't':
    cfg->source = SOURCE_TIME;
    break;
  case 'u':
    cfg->sink = SINK_UUID;
    break;
  case -1:
    cfg->source = SOURCE_NONE;
    cfg->sink = SINK_NONE;
    print_help(program);
    return -1;
  case -2:
    cfg->source = SOURCE_NONE;
    cfg->sink = SINK_NONE;
    print_version(program);
    return -1;
  default:
    fprintf(stderr,
            "%s: invalid option -- %c\n"
            "Try `%s --help' for more information.\n",
            program, flag, program);
    return 1;
  }
  return 0;
}


int parse_long_option(const char* option, struct config_t* cfg) {
  int ret;
  if(!strcmp(option + 2, "help"))
    ret = parse_short_option(-1, cfg);
  else if(!strcmp(option + 2, "version"))
    ret = parse_short_option(-2, cfg);
  else if(!strcmp(option + 2, "cdef"))
    ret = parse_short_option('c', cfg);
  else if(!strcmp(option + 2, "random"))
    ret = parse_short_option('r', cfg);
  else if(!strcmp(option + 2, "time"))
    ret = parse_short_option('t', cfg);
  else if(!strcmp(option + 2, "uuid"))
    ret = parse_short_option('u', cfg);
  else {
    fprintf(stderr,
            "%s: unrecognised option `%s'\n"
            "Try `%s --help' for more information.\n",
            program, option, program);
    ret = 1;
  }
  return ret;
}


int parse_conf(int argc, char** argv, struct config_t* cfg) {
  int i;

  if(!cfg) {
    fprintf(stderr,
            "%s: Programmer error at %s:%d\n", program, __FILE__, __LINE__);
    abort();
  }

  memset(cfg, 0, sizeof(*cfg));

  /* By default, uuidcdef outputs a SINK_CDEF */
  if (strstr(program, "cdef"))
    cfg->sink = SINK_CDEF;

  for(i = 1; i < argc; ++i) {
    int state = PARSE_UNKNOWN;
    /* Iterate through the option and decide what to do with it */
    char* c;
    for(c = argv[i]; c; c && ++c) {
      switch(state) {
      case PARSE_INVALID:
        fprintf(stderr,
                "%s: unrecognised option `%s'\n"
                "Try `%s --help' for more information.\n",
                program, argv[i], program);
        return 1;
      case PARSE_FLAGS:
        switch(*c) {
        case '-':
          state = PARSE_LONG_OPTION;
          break;
        default:
          state = PARSE_SHORT_OPTIONS;
          --c;
        }
        break;
      case PARSE_SHORT_OPTIONS:
        if(*c) {
          int ret = parse_short_option(*c, cfg);
          if(ret > 0)
            return ret;
          else if(ret < 0)
            return 0;
        } else
          c = NULL;
        break;
      case PARSE_LONG_OPTION: {
        int ret = parse_long_option(argv[i], cfg);
        if(ret > 0)
          return ret;
        else if(ret < 0)
          return 0;
        c = NULL;
        break;
      }
      default:
        switch(*c) {
        case '-':
          state = PARSE_FLAGS;
          break;
        default:
          state = PARSE_INVALID;
        }
      }
    }
  }

  return 0;
}


typedef const char* (*uuid_output_fn_t)(const uuid_t);
static char uuid_unparse_buf[60];
const char* uuid_unparse_x_(const uuid_t uuid) {
  /* This function implicitly trusts uuid_unparse. */
  unsigned int a, b, c, d, e, f, g, h, i, j, k;
  int ret;
  uuid_unparse(uuid, uuid_unparse_buf);
  ret = sscanf(uuid_unparse_buf,
               "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
               &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k);
  if(ret != 11) {
    uuid_unparse_buf[59] = '\0';
    fprintf(stderr,
            "%s: libuuid error at %s:%d\n", program, __FILE__, __LINE__);
    fprintf(stderr,
            "uuid_unparse() returned `%s'.\n", uuid_unparse_buf);
    abort();
  }
  sprintf(uuid_unparse_buf,
          "{0x%08x, "
          "0x%04x, "
          "0x%04x, "
          "{0x%02x, 0x%02x, "
          "0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x}}",
          a, b, c, d, e, f, g, h, i, j, k);
  return uuid_unparse_buf;
}
const char* uuid_unparse_(const uuid_t uuid) {
  uuid_unparse(uuid, uuid_unparse_buf);
  return uuid_unparse_buf;
}


#define BUFFER_SIZE 100
#define LENGTH 36
int main(int argc, char** argv) {
  /* Configuration */
  struct config_t cfg;
  /* Return value */
  int ret;

  /* Parse the command line arguments */
  program = argv[0];
  ret = parse_conf(argc, argv, &cfg);
  if(!ret)
  {
    /* Function that will generate the correct output */
    uuid_output_fn_t uuid_output_fn = NULL;
    /* Static buffer to hold the UUID. */
    uuid_t uuid;
    memset(uuid, 0, sizeof(uuid));

    /* Generate the UUID, using the method requested. */
    switch(cfg.source) {
    case SOURCE_RANDOM:
      uuid_generate_random(uuid);
      break;
    case SOURCE_TIME:
      uuid_generate_time(uuid);
      break;
    case SOURCE_AUTO:
      uuid_generate(uuid);
      break;
    default:
      ;
    }

    switch(cfg.sink) {
    case SINK_CDEF:
      uuid_output_fn = &uuid_unparse_x_;
      break;
    case SINK_UUID:
      uuid_output_fn = &uuid_unparse_;
      break;
    default:
      uuid_output_fn = NULL;
    }

    /* Do the right kind of output, using the method requested. */
    if(uuid_output_fn)
      printf("%s\n", uuid_output_fn(uuid));
  }

  return ret;
}
