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
# $Id: rules.mk,v 1.1 2005/10/21 13:18:22 sfllaw Exp $

default: $(UUID_OBJS) $(UUID_BINS) uuid/bin/uuidcdef

uuid/libuuid.a: $(patsubst %.c,%.o,$(wildcard uuid/*.c))

uuid/bin/uuidcdef: uuid/bin/uuidgen
	$(LN_S) $(notdir $<) $@

uuid/bin/%: uuid/bin/%.o $(with_uuid_static)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

uuid/bin/%: LDLIBS+=$(with_uuid)
