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
# $Id: rules.mk,v 1.21 2005/01/05 23:21:12 pphaneuf Exp $

.PHONY: tests

ifeq ("$(enable_loader)", "no")
tests: default tests/testmain
else
tests: default tests/testmain tests/testobj.dll
endif
	@echo "Running tests:"
	@cd tests && ./testmain $(TESTS)

tests/testmain: tests/testmain.o $(patsubst %.cpp,%.o,$(wildcard tests/test[0-9][0-9][0-9].cpp)) libxplc.a libxplc-cxx.a

tests/testobj.dll: tests/testobj.o libxplc-cxx.a

