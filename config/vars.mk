# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
# Copyright (C) 2002, Net Integration Technologies, Inc.
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Library General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.
#
# $Id: vars.mk,v 1.14 2002/03/29 23:12:31 pphaneuf Exp $

DISTCLEAN+=config/config.mk ChangeLog.bak config/depends.mk
REALCLEAN+=ChangeLog

SIMPLETARGETS+=dist ChangeLog clean dustclean realclean distclean

# Function that returns "even" or "odd", depending on the value passed.
oddeven = $(filter even odd,$(foreach d,0 2 4 6 8,$(1:%$d=even)) $(foreach d,1 3 5 7 9,$(1:%$d=odd)))

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

ifeq ("$(enable_fatal_warnings)", "yes")
CXXFLAGS+=-Werror
endif

ifneq ("$(enable_optimization)", "no")
CXXFLAGS+=-O2
endif

ifneq ("$(enable_warnings)", "no")
CXXFLAGS+=-pedantic -Wall -Wold-style-cast -Woverloaded-virtual
endif

ifneq ("$(enable_rtti)", "yes")
CXXFLAGS+=-fno-rtti
endif

ifneq ("$(enable_exceptions)", "yes")
CXXFLAGS+=-fno-exceptions
endif

