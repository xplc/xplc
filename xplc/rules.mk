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
# $Id: rules.mk,v 1.8 2002/03/29 23:37:14 pphaneuf Exp $

LIBXPLC_OBJS:=$(patsubst %.cpp,%.o,$(wildcard xplc/*.cpp))

libxplc_s.a: $(LIBXPLC_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

libxplc.so.$(VERSION): $(LIBXPLC_OBJS) -ldl
	$(LINK.cc) -shared -Wl,-soname,$(LIBXPLC_SONAME) $^ -o $@

