# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
# Copyright (C) 2002, Net Integration Technologies, Inc.
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
#
# $Id: vars.mk,v 1.32 2003/12/12 21:28:33 pphaneuf Exp $

DEPFILES:=$(shell find . -name '.*.d')

CLEAN+=$(shell find . -name '*.o' -print) libxplc.so* $(DEPFILES) $(addprefix debian/,$(shell cat debian/.cvsignore))
DISTCLEAN+=config/config.mk include/xplc/autoconf.h ChangeLog.bak
REALCLEAN+=ChangeLog autom4te.cache include/xplc/autoconf.h.in

SIMPLETARGETS+=ChangeLog clean dustclean realclean distclean doxygen clean-doxygen

# Function that returns "even" or "odd", depending on the value passed.
oddeven = $(filter even odd,$(foreach d,0 2 4 6 8,$(1:%$d=even)) $(foreach d,1 3 5 7 9,$(1:%$d=odd)))

VERSION_MAJOR:=$(word 1,$(subst ., ,$(PACKAGE_VERSION)))
VERSION_MINOR:=$(word 2,$(subst ., ,$(PACKAGE_VERSION)))
VERSION_PATCH:=$(word 3,$(subst ., ,$(PACKAGE_VERSION)))

# The 'S' option to 'ar' seems to cause problem on Solaris?
#ARFLAGS=rcS
ARFLAGS=rc

RANLIB=ranlib

CXXFLAGS+=-pipe -Iinclude

ifneq ("$(filter-out no,$(enable_debug))", "")
DEBUG:=$(enable_debug)
endif

ifdef DEBUG
CXXFLAGS+=-ggdb -DDEBUG
ifneq ("$(DEBUG)", "yes")
CXXFLAGS+=-DDEBUG_$(DEBUG)
endif
else
CXXFLAGS+=-DNDEBUG
endif

ifeq ("$(call oddeven,$(VERSION_MINOR))", "odd")
ifndef enable_unstable
enable_unstable=yes
endif
endif

ifeq ("$(enable_unstable)", "yes")
CXXFLAGS+=-DUNSTABLE
endif

ifeq ("$(enable_fatal_warnings)", "yes")
CXXFLAGS+=-Werror
endif

ifneq ("$(enable_optimization)", "no")
CXXFLAGS+=-O2
endif

ifneq ("$(enable_warnings)", "no")
CXXFLAGS+=-pedantic -Wall -Woverloaded-virtual
ifeq ("$(enable_warnings)", "yes")
CXXFLAGS+=-Wold-style-cast
endif
endif

ifneq ("$(enable_rtti)", "yes")
CXXFLAGS+=-fno-rtti
endif

ifneq ("$(enable_exceptions)", "yes")
CXXFLAGS+=-fno-exceptions
endif

ifneq ("$(enable_pic)", "no")
CXXFLAGS+=-fpic
endif

ifeq ("$(so_style)", "darwin")
SHARED=-bundle
endif

ifeq ("$(so_style)", "sysv")
SONAMEOPT=-Wl,-h
SHARED=-shared $(if $(SONAME),$(SONAMEOPT)$(SONAME)) -Wl,-z,defs,--version-script=config/exports.map
endif

