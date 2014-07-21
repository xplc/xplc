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
# $Id: vars.mk,v 1.41 2005/10/21 13:08:27 sfllaw Exp $

DEPFILES:=$(shell find . -name '.*.d')

DUSTCLEAN+=$(shell find . -name '*~' -o -name '.\#*')
CLEAN+=$(shell find . -name '*.o') libxplc.so* $(DEPFILES) $(patsubst /%,%,$(shell grep '^/debian\/' .gitignore | grep -v control)) autom4te.cache xplc-[0-9]*
DISTCLEAN+=config/config.mk include/autoconf.h ChangeLog.bak
REALCLEAN+=ChangeLog include/autoconf.h.in debian/control

SIMPLETARGETS+=ChangeLog clean dustclean realclean distclean doxygen clean-doxygen

# Function that returns "even" or "odd", depending on the value passed.
oddeven = $(filter even odd,$(foreach d,0 2 4 6 8,$(1:%$d=even)) $(foreach d,1 3 5 7 9,$(1:%$d=odd)))

VERSION_MAJOR:=$(word 1,$(subst ., ,$(PACKAGE_VERSION)))
VERSION_MINOR:=$(word 2,$(subst ., ,$(PACKAGE_VERSION)))
VERSION_PATCH:=$(word 3,$(subst ., ,$(PACKAGE_VERSION)))

DIST=$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)

# The 'S' option to 'ar' seems to cause problem on Solaris?
#ARFLAGS=rcS
ARFLAGS=rc

RANLIB=ranlib

CXXFLAGS+=-pipe -Iinclude

ifeq ("$(so_style)", "darwin")
SHARED=-bundle
endif

ifeq ("$(so_style)", "sysv")
SONAMEOPT=-Wl,-h
SHARED=-shared $(if $(SONAME),$(SONAMEOPT)$(SONAME)) -Wl,-z,defs,--version-script=config/exports.map
endif

