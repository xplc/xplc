# This file is example code for XPLC (http://xplc.sourceforge.net/),
# and is put into the public domain.

.PHONY: default clean

# the UNSTABLE flag is there because we agree to use interfaces that
# have not been frozen yet.
CPPFLAGS+=-DUNSTABLE -I../simple-module

default: example

clean:
	rm -f example *~ *.o

example: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(LINK.cc) $^ -lxplc -lxplc-cxx -o $@

