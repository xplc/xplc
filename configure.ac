# Process this file with autoconf to produce a configure script.
#
# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
# Copyright (C) 2002-2004, Net Integration Technologies, Inc.
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

AC_INIT(XPLC, 0.3.10, pp@ludusdesign.com)
AC_REVISION($Id: configure.ac,v 1.34 2004/10/07 03:17:09 sfllaw Exp $)

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
AC_PROG_LN_S

AC_HEADER_DIRENT
AC_CHECK_HEADERS([limits.h])

AC_CHECK_PROGS([CVS2CL], [cvs2cl.pl cvs2cl], [no])

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
if test "$with_dlopen" = "no" && test "$with_dyld" = "no"; then
    enable_loader=no
fi

if test "$enable_loader" != "no"; then
    AC_DEFINE(ENABLE_LOADER, 1, [Define if you want to enable dynamic loading.])
fi

if test "$enable_optimization" != "no"; then
    CXXFLAGS="$CXXFLAGS -O2"
fi

if test -z "$enable_debug"; then
    enable_debug=no
fi

if test "$enable_debug" != "no"; then
    CXXFLAGS="$CXXFLAGS -ggdb -DDEBUG"
    if test "$enable_debug" != "yes"; then
        CXXFLAGS="$CXXFLAGS -DDEBUG_$enable_debug"
    fi
else
    CXXFLAGS="$CXXFLAGS -DNDEBUG"
fi

if test "$enable_fatal_warnings" = "yes"; then
    CXXFLAGS="$CXXFLAGS -Werror"
fi

if test "$enable_warnings" != "no"; then
    CXXFLAGS="$CXXFLAGS -Wall -Woverloaded-virtual"
    if test "$enable_warnings" = "yes"; then
        CXXFLAGS="$CXXFLAGS -Wold-style-cast"
    fi
fi

if test "$enable_rtti" != "yes"; then
    CXXFLAGS="$CXXFLAGS -fno-rtti"
fi

if test "$enable_exceptions" != "yes"; then
    CXXFLAGS="$CXXFLAGS -fno-exceptions"
fi

if test "$enable_pic" != "no"; then
    CXXFLAGS="$CXXFLAGS -fpic"
fi

pc_version=
libdir_version=
lib_prefix_version=
if test "$(echo $PACKAGE_VERSION | awk -F. '{ print $2 % 2}')" -eq 1; then
    AC_MSG_WARN([Unstable release, the API might change in the next release.])
    enable_unstable=yes
    includedir="$includedir/xplc-${PACKAGE_VERSION}"
    pc_version="-${PACKAGE_VERSION}"
    libdir_version="/xplc-${PACKAGE_VERSION}"
    lib_prefix_version="../"
fi

if test "$enable_unstable" = "yes"; then
    CXXFLAGS="$CXXFLAGS -DUNSTABLE"
fi

AC_SUBST(pc_version)
AC_SUBST(libdir_version)
AC_SUBST(lib_prefix_version)
AC_SUBST(enable_loader)
AC_SUBST(with_dlopen)
AC_SUBST(so_style)
AC_SUBST(CVS2CL)

AC_CONFIG_FILES([config/config.mk dist/xplc.pc dist/xplc-uninstalled.pc examples/simple-module/Makefile examples/simple-module-user/Makefile])
AC_CONFIG_HEADERS([include/autoconf.h])

AC_OUTPUT

if test "$enable_loader" = "no"; then
    AC_MSG_WARN([Dynamic loading is disabled.])
fi

