# This file is example code for XPLC (http://xplc.sourceforge.net/),
# and is put into the public domain.

.PHONY: default clean

# the UNSTABLE flag is there because we agree to use interfaces that
# have not been frozen yet.
CPPFLAGS+=-DUNSTABLE

default: example.so

clean:
	rm -f example.so *~ *.o

%.so:
	$(LINK.cc) -shared $^ -lxplc-cxx -o $@

example.so: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

