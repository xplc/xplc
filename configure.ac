# Process this file with autoconf to produce a configure script.
#
# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
# Copyright (C) 2002, Net Integration Technologies, Inc.
#
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of the
# License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA

AC_INIT(xplc, 0.1.6, pp@ludusdesign.com)
AC_REVISION($Id: configure.ac,v 1.7 2002/11/30 10:48:09 pphaneuf Exp $)

AC_ARG_ENABLE(debug,
              AC_HELP_STRING([--enable-debug],
                             [debugging options]))

AC_ARG_ENABLE(fatal-warnings,
              AC_HELP_STRING([--enable-fatal-warnings],
                             [turn warnings into errors]))

AC_ARG_ENABLE(optimization,
              AC_HELP_STRING([--disable-optimization],
                             [optimization options]))

AC_ARG_ENABLE(warnings,
              AC_HELP_STRING([--disable-warnings],
                             [extra warnings]))

AC_ARG_ENABLE(unstable,
              AC_HELP_STRING([--enable-unstable],
                             [allow unstable interfaces in stable version]))

AC_ARG_ENABLE(rtti,
              AC_HELP_STRING([--enable-rtti],
                             [C++ run-time type identification (compiler)]))

AC_ARG_ENABLE(exceptions,
              AC_HELP_STRING([--enable-exceptions],
                             [C++ exceptions (compiler)]))

AC_ARG_WITH(dlopen,
            AC_HELP_STRING([--with-dlopen],
                           [dlopen]))

AC_CONFIG_SRCDIR([include/xplc/xplc.h])

AC_LANG(C++)

AC_PROG_CXX
AC_PROG_INSTALL

if test "$with_dlopen" != "no"; then
    AC_SEARCH_LIBS(dlopen, dl, with_dlopen=$ac_cv_search_dlopen, with_dlopen=no)
    test "$with_dlopen" = "none required" && with_dlopen=
    test "$with_dlopen" = "no" || AC_DEFINE(WITH_DLOPEN, 1, [Define if you want to use dlopen.])
fi

AC_HEADER_DIRENT
AC_CHECK_HEADERS(dlfcn.h)

AC_SUBST(enable_debug)
AC_SUBST(enable_fatal_warnings)
AC_SUBST(enable_optimization)
AC_SUBST(enable_warnings)
AC_SUBST(enable_unstable)
AC_SUBST(enable_rtti)
AC_SUBST(enable_exceptions)
AC_SUBST(with_dlopen)

AC_CONFIG_FILES([config/config.mk])
AC_CONFIG_HEADERS([include/xplc/autoconf.h])

AC_OUTPUT

if test "$with_dlopen" = "no"; then
    AC_MSG_WARN([dynamic loading is disabled.])
fi

