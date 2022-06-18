GCC=gcc
INSTALL=/usr/bin/install
LDCONFIG=/sbin/ldconfig

lib:
	$(GCC) -fPIC -std=c99 -O2 -fPIC -march=native -mavx2 -shared -o libxcorr.so src/xcorr.c

install:
	$(INSTALL) include/xcorr.h /usr/local/include/
	$(INSTALL) libxcorr.so /usr/local/lib/
	$(LDCONFIG)

all: lib install
