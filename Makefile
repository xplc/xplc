# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000, Pierre Phaneuf
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
# $Id: Makefile,v 1.8 2002/09/27 21:10:27 pphaneuf Exp $

.PHONY: default all

default: all

include config/version.mk

-include config/config.mk

GARBAGES+=$(wildcard libxplc.so.*)
DISTCLEAN+=config.cache config.log config.status
REALCLEAN+=configure README xplc.spec

include $(wildcard */vars.mk)

include $(wildcard */rules.mk)

all: $(TARGETS)

