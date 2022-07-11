# $Id: Makefile,v 1.3 2005/12/17 15:50:11 sonarnerd Exp $
#
# Makefile for common C++ classes
# Copyright (C) 2005 Jussi Laako
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

CXX = g++
CXXFLAGS = -march=pentium2 -mcpu=pentium4 -O3 -fprefetch-loop-arrays
CXXFLAGS += -Wall -Werror
CXXFLAGS += -g
TESTLIBS = -lm -lrt -lpthread -lefence
DEFS = -D_REENTRANT -D_THREAD_SAFE -DUSE_NPTL
INCS = -I.

PREFIX = /usr/local

CCEXT = cc
HEXT = hh
OBJEXT = o
LIBEXT = a

SRCS = DateTime.$(CCEXT) \
	SocketAddr.$(CCEXT) \
	SocketOp.$(CCEXT) \
	String.$(CCEXT) \
	Threads.$(CCEXT)

OBJS = DateTime.$(OBJEXT) \
	SocketAddr.$(OBJEXT) \
	SocketOp.$(OBJEXT) \
	String.$(OBJEXT) \
	Threads.$(OBJEXT)

default: all

all: libcommoncpp.$(LIBEXT) stringtest datetimetest sockettest

.$(CCEXT).$(OBJEXT): $(SRCS)
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCS) -c $<

libcommoncpp.$(LIBEXT): $(OBJS)
	ar rc libcommoncpp.$(LIBEXT) $(OBJS)
	ranlib libcommoncpp.$(LIBEXT)

stringtest: libcommoncpp.$(LIBEXT) StringTest.$(CCEXT)
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCS) -o stringtest StringTest.$(CCEXT) libcommoncpp.$(LIBEXT) $(TESTLIBS)

datetimetest: libcommoncpp.$(LIBEXT) DateTimeTest.$(CCEXT)
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCS) -o datetimetest DateTimeTest.$(CCEXT) libcommoncpp.$(LIBEXT) $(TESTLIBS)

sockettest: libcommoncpp.$(LIBEXT) SocketTest.$(CCEXT)
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCS) -o sockettest SocketTest.$(CCEXT) libcommoncpp.$(LIBEXT) $(TESTLIBS)

install: libcommoncpp.$(LIBEXT)
	install -m 755 -d $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Alloc.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Compilers.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Condition.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/DateTime.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Exception.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Generic.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Mutex.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/RWLock.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Semaphore.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/SocketAddr.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/SocketOp.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/SocketTypes.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/String.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 644 commoncpp/Threads.$(HEXT) $(PREFIX)/include/commoncpp
	install -m 755 -d $(PREFIX)/lib
	install -m 644 libcommoncpp.$(LIBEXT) $(PREFIX)/lib

clean:
	rm -f core* *.$(OBJEXT) *~

cleanall:
	rm -f libcommoncpp.$(LIBEXT) datetimetest stringtest sockettest Makefile.dep core* *.$(OBJEXT) *~

Makefile.dep: $(SRCS)
	$(CXX) -MM $(DEFS) $(INCS) $(SRCS) >Makefile.dep

include Makefile.dep

