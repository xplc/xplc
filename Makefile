# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000, Pierre Phaneuf
# Copyright (C) 2002-2004, Net Integration Technologies, Inc.
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
# $Id: Makefile,v 1.13 2004/05/21 20:21:35 pphaneuf Exp $

.PHONY: default

default:

-include config/config.mk

CLEAN+=$(wildcard libxplc*.a libxplc.so.* doxygen)
DISTCLEAN+=config.cache config.log config.status dist/xplc.pc dist/xplc-uninstalled.pc xplc-uninstalled.pc
REALCLEAN+=configure README xplc.spec

include $(wildcard */vars.mk)

include $(wildcard */rules.mk)

