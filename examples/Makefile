# This file is example code for XPLC (http://xplc.sourceforge.net/),
# and is put into the public domain.

SUBDIRS=$(patsubst %/Makefile,%,$(wildcard */Makefile))

.PHONY: default clean $(SUBDIRS)
default: $(SUBDIRS)

clean: $(SUBDIRS)

simple-module-user: simple-module

# This is so that the example builds from within the XPLC package.
export CPPFLAGS+=-I../../include
export LDFLAGS+=-L../.. 

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

