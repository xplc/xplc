# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2001, Pierre Phaneuf
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
# $Id: rules.mk,v 1.5 2002/03/29 21:18:02 pphaneuf Exp $

tests/test005/test: tests/test005/test.o tests/testmain.o libxplc_s.a -ldl tests/test005/testobj.dll
	$(LINK.cc) tests/test005/test.o tests/testmain.o libxplc_s.a -ldl $(LOADLIBES) $(LDLIBS) -o $@

tests/test005/testobj.dll: tests/test005/testobj.o
	$(LINK.cc) -shared -o $@ $^

