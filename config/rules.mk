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
# $Id: rules.mk,v 1.17 2002/09/27 21:10:27 pphaneuf Exp $

.PHONY: ChangeLog dist dustclean clean distclean realclean installdirs install uninstall

dist: distclean ChangeLog README xplc.spec
	autoconf
	autoheader
	rm -rf autom4te.cache

ChangeLog:
	rm -f ChangeLog ChangeLog.bak
	cvs2cl.pl --utc -U config/cvs-users

README: dist/README.in config/version.mk
	sed $< -e 's%@VERSION@%$(VERSION)%g' > $@

xplc.spec: dist/xplc.spec.in config/version.mk
	sed $< -e 's%@VERSION@%$(VERSION)%g' > $@

dustclean:
	rm -f $(shell find . -name 'core' -print)
	rm -f $(shell find . -name '*~' -print)
	rm -f $(shell find . -name '.#*' -print)

clean: dustclean
	rm -f $(shell find . -name '*.o' -print)
	rm -f $(wildcard $(GARBAGES) $(TARGETS))

distclean: clean
	rm -f $(wildcard $(DISTCLEAN))

realclean: distclean
	rm -f $(wildcard $(REALCLEAN))

installdirs:
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)/xplc

install: $(TARGETS) installdirs
	$(INSTALL_PROGRAM) libxplc.so.$(VERSION) $(DESTDIR)$(libdir)
	$(INSTALL_DATA) libxplc.a $(DESTDIR)$(libdir)
	$(INSTALL_DATA) $(wildcard include/xplc/*.h) $(DESTDIR)$(includedir)/xplc
	ln -s libxplc.so.$(VERSION) $(DESTDIR)$(libdir)/libxplc.so
	ln -s libxplc.a $(DESTDIR)$(libdir)/libxplc_s.a

uninstall:
	rm -f $(DESTDIR)$(libdir)/libxplc.so.$(VERSION) $(DESTDIR)$(libdir)/libxplc.so
	rm -f $(DESTDIR)$(libdir)/libxplc.a $(DESTDIR)$(libdir)/libxplc_s.a
	rm -rf $(DESTDIR)$(includedir)/xplc

ifeq ($(filter-out $(SIMPLETARGETS),$(MAKECMDGOALS)),$(MAKECMDGOALS))

config/config.mk: config/config.mk.in configure
	@echo "Please run './configure'."
	@exit 1

configure: configure.in
	autoconf
	autoheader

config/depends.mk: config/config.mk
	@echo "Building dependencies file ($@)"
	@$(foreach DEP,$(CXXDEPS),$(COMPILE.cc) -M $(DEP) | sed -e 's|^.*:|$(dir $(DEP))&|' >> $@;)

-include config/depends.mk

endif

