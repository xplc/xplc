# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
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
# $Id: rules.mk,v 1.19 2004/05/21 20:21:35 pphaneuf Exp $

default: libxplc.a libxplc_s.a libxplc.so xplc-uninstalled.pc

libxplc.a libxplc.so: $(patsubst %.cpp,%.o,$(wildcard xplc/*.cpp))

libxplc.so: libxplc-cxx.a

xplc-uninstalled.pc: dist/xplc-uninstalled.pc
	cp $^ $@

