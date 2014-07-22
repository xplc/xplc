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
# $Id: vars.mk,v 1.13 2002/12/05 03:48:19 pphaneuf Exp $

# This number should only be increased when a new version breaks
# binary compatibility with the previous one. It is used to set
# the soname of the shared library.
libxplc.so: BINARY_VERSION:=0

ifeq ("$(call oddeven,$(VERSION_MINOR))", "even")
libxplc.so: SONAME:=libxplc.so.$(BINARY_VERSION)
else
libxplc.so: SONAME:=libxplc.so.$(PACKAGE_VERSION)-unstable
endif

ifneq ("$(enable_loader)", "no")
ifneq ("$(with_dlopen)", "no")
libxplc.so: LDLIBS+=$(with_dlopen)
endif
endif

