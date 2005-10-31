# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2005, Net Integration Technologies, Inc.
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
# $Id: vars.mk,v 1.1 2005/10/21 13:18:22 sfllaw Exp $

UUID_BINS=uuid/bin/uuidgen uuid/bin/tst_uuid
UUID_OBJS=$(addsuffix .o,$(UUID_BINS))

CLEAN+=$(UUID_BINS) $(UUID_OBJS) uuid/bin/uuidcdef uuid/libuuid.a
DISTCLEAN+=uuid/uuid_types.h

uuid/%.o: CFLAGS+=-I. -include include/autoconf.h

