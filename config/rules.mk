# XPLC - Cross-Platform Lightweight Components
# Copyright (C) 2000-2003, Pierre Phaneuf
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
# $Id: rules.mk,v 1.31 2003/11/15 05:34:38 pphaneuf Exp $

.PHONY: ChangeLog dist dustclean clean distclean realclean installdirs install uninstall doxygen clean-doxygen

%.o: %.cpp
	@$(COMPILE.cpp) -M -E $< | sed -e 's|^.*:|$@:|' > $(dir $@).$(notdir $(@:.o=.d))
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

%.s: %.cpp
	@$(COMPILE.cpp) -M -E $< | sed -e 's|^.*:|$@:|' > $(dir $@).$(notdir $(@:.s=.d))
	$(COMPILE.cpp) $(OUTPUT_OPTION) -S $<

%: %.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

lib%_s.a: lib%.a
	ln -sf $^ $@

%.a:
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

%.so:
	$(LINK.cc) $(SHARED) $^ -o $@

%.dll:
	$(LINK.cc) $(SHARED) $^ -o $@

dist: ChangeLog README xplc.spec distclean
	autoconf
	autoheader
	rm -rf autom4te.cache

ChangeLog:
	rm -f ChangeLog ChangeLog.bak
	cvs2cl.pl --utc -U config/cvs-users

doxygen: clean-doxygen
	doxygen

clean-doxygen:
	rm -rf doxygen

README: dist/README.in
	sed $< -e 's%@VERSION@%$(PACKAGE_VERSION)%g' > $@

xplc.spec: dist/xplc.spec.in
	sed $< -e 's%@VERSION@%$(PACKAGE_VERSION)%g' > $@

dustclean:
	-rm -rf $(shell find . -name '*~' -print) $(shell find . -name '.#*' -print)

clean: dustclean clean-doxygen
	-rm -rf $(wildcard $(CLEAN))

distclean: clean
	-rm -rf $(wildcard $(DISTCLEAN))

realclean: distclean
	-rm -rf $(wildcard $(REALCLEAN))

installdirs:
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)/xplc

install: default installdirs
	$(INSTALL_PROGRAM) libxplc.so $(DESTDIR)$(libdir)/libxplc.so.$(PACKAGE_VERSION)
	$(INSTALL_DATA) libxplc.a $(DESTDIR)$(libdir)
	$(INSTALL_DATA) libxplc-cxx.a $(DESTDIR)$(libdir)
	$(INSTALL_DATA) $(wildcard include/xplc/*.h) $(DESTDIR)$(includedir)/xplc
	ln -s libxplc.so.$(PACKAGE_VERSION) $(DESTDIR)$(libdir)/libxplc.so
	ln -s libxplc.a $(DESTDIR)$(libdir)/libxplc_s.a

uninstall:
	rm -f $(DESTDIR)$(libdir)/libxplc.so.$(PACKAGE_VERSION) $(DESTDIR)$(libdir)/libxplc.so
	rm -f $(DESTDIR)$(libdir)/libxplc.a $(DESTDIR)$(libdir)/libxplc_s.a
	rm -rf $(DESTDIR)$(includedir)/xplc

ifeq ($(filter-out $(SIMPLETARGETS),$(MAKECMDGOALS)),$(MAKECMDGOALS))

config/config.mk: config/config.mk.in configure
	@echo "Please run './configure'."
	@exit 1

configure: configure.ac
	autoconf
	autoheader

-include $(DEPFILES) /dev/null

endif

