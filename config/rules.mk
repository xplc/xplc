# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2002, Pierre Phaneuf
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
# $Id: rules.mk,v 1.12 2002/03/29 23:36:48 pphaneuf Exp $

.PHONY: ChangeLog dist dustclean clean distclean realclean installdirs install

dist: distclean ChangeLog README
	autoconf

ChangeLog:
	rm -f ChangeLog ChangeLog.bak
	cvs2cl.pl --utc -U config/cvs-users

README: dist/README.in
	sed $< -e 's%@VERSION@%$(VERSION)%g' > $@

dustclean:
	rm -f $(shell find . -name 'core' -print)
	rm -f $(shell find . -name '*~' -print)
	rm -f $(shell find . -name '.#*' -print)

clean: dustclean
	rm -f $(shell find . -name '*.o' -print)
	rm -f $(GARBAGES)
	rm -f $(TARGETS)

distclean: clean
	rm -f $(DISTCLEAN)

realclean: distclean
	rm -f $(REALCLEAN)

installdirs:
	mkdir -p $(libdir)
	mkdir -p $(includedir)/xplc

install: $(TARGETS) installdirs
	$(INSTALL_PROGRAM) libxplc.so.$(VERSION) $(libdir)
	$(INSTALL_DATA) libxplc_s.a $(libdir)
	$(INSTALL_DATA) $(wildcard include/xplc/*.h) $(includedir)/xplc
	ln -s libxplc.so.$(VERSION) $(libdir)/libxplc.so

ifeq ($(filter-out $(SIMPLETARGETS),$(MAKECMDGOALS)),$(MAKECMDGOALS))

config/config.mk: config/config.mk.in configure
	@echo "Please run './configure'."
	@exit 1

configure: configure.in
	autoconf

config/depends.mk: config/config.mk
	@echo "Building dependencies file ($@)"
	@$(foreach DEP,$(CXXDEPS),$(COMPILE.cc) -M $(DEP) | sed -e 's|^.*:|$(dir $(DEP))&|' >> $@;)

-include config/depends.mk

endif

