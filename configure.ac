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

AC_INIT(XPLC, 0.3.3, pp@ludusdesign.com)
AC_REVISION($Id: configure.ac,v 1.17 2004/03/20 19:51:46 pphaneuf Exp $)

AC_CANONICAL_HOST

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

AC_ARG_ENABLE(pic,
              AC_HELP_STRING([--disable-pic],
                             [generation of position-independent code]))

AC_ARG_ENABLE(loader,
              AC_HELP_STRING([--disable-loader],
                             [dynamic loading]))

AC_ARG_WITH(dlopen,
            AC_HELP_STRING([--with-dlopen],
                           [dlopen]))

AC_ARG_WITH(dyld,
            AC_HELP_STRING([--with-dyld],
                           [dyld]))

AC_CONFIG_SRCDIR([include/xplc/xplc.h])

AC_LANG(C++)

AC_PROG_CXX
AC_PROG_INSTALL

case "$host_os" in
darwin*|rhapsody*)
    so_style=darwin
    ;;
*)
    so_style=sysv
    ;;
esac

if test "$with_dlopen" != "no"; then
    AC_CHECK_HEADERS(dlfcn.h)
    AC_SEARCH_LIBS(dlopen, dl, with_dlopen=$ac_cv_search_dlopen, with_dlopen=no)
    test "$with_dlopen" = "none required" && with_dlopen=
    test "$with_dlopen" = "no" || AC_DEFINE(WITH_DLOPEN, 1, [Define if you have dlopen.])
fi

if test "$with_dyld" != "no"; then
    AC_CHECK_HEADERS(mach-o/dyld.h)
    AC_SEARCH_LIBS(NSCreateObjectFileImageFromFile, System, with_dyld=$ac_cv_search_NSCreateObjectFileImageFromFile, with_dyld=no)
    test "$with_dyld" = "none required" && with_dyld=
    test "$with_dyld" = "no" || AC_DEFINE(WITH_DYLD, 1, [Define if you have dyld.])
fi

# dyld not really supported yet
#if test "$with_dlopen" = "no" && test "$with_dyld" = "no"; then
if test "$with_dlopen" = "no"; then
    enable_loader=no
fi

if test "$enable_loader" != "no"; then
    AC_DEFINE(ENABLE_LOADER, 1, [Define if you want to enable dynamic loading.])
fi

AC_HEADER_DIRENT

AC_SUBST(enable_debug)
AC_SUBST(enable_fatal_warnings)
AC_SUBST(enable_optimization)
AC_SUBST(enable_warnings)
AC_SUBST(enable_unstable)
AC_SUBST(enable_rtti)
AC_SUBST(enable_exceptions)
AC_SUBST(enable_pic)
AC_SUBST(enable_loader)
AC_SUBST(with_dlopen)
AC_SUBST(so_style)

AC_CONFIG_FILES([config/config.mk])
AC_CONFIG_HEADERS([include/xplc/autoconf.h])

AC_OUTPUT

if test "$enable_loader" = "no"; then
    AC_MSG_WARN([Dynamic loading is disabled.])
fi

