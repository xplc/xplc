# XPLC - Cross-Platform Lightweight Components
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
# $Id: version.mk,v 1.3 2002/09/14 04:23:51 pphaneuf Exp $

VERSION_MAJOR:=0
VERSION_MINOR:=1
VERSION_PATCH:=4

VERSION:=$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

# This number should only be increased when a new version breaks
# binary compatibility with the previous one. It is used to set
# the soname of the shared library.
BINARY_VERSION:=0

