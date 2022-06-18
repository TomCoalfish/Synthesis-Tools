# File:		Makefile
# Module: 
# Comment:  
# Copyright(C) 2018 Bob Mittmann. All Rights Reserved.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

PROG = glwdf

CFILES = ../src/vec-fp64.c ../src/lwdf-fp64.c ../src/lwdf-fp64-freq.c \
	plot/plot-color.c plot/plot-figure.c plot/plot-series.c \
	plot/plot-freqresp.c plot/plot-gtk.c \
	glwdf-freq.c glwdf-time.c glwdf-app.c 

OFILES = $(CFILES:.c=.o)

LIBS = m pthread

INCPATH	= ../include plot  .
LIBPATH =

DBGOPTS = -g 

OPTIONS	= $(DBGOPTS) -DDEBUG=1
#OPTIONS	= $(DBGOPTS) -mno-cygwin

#GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

GTKLIB = `pkg-config --libs gtk+-3.0`
GTKCFLAGS = `pkg-config --cflags gtk+-3.0` 

SFLAGS	= -Wall
CFLAGS	= -Wall -Ofast
LDFLAGS	= $(GTKLIB) -export-dynamic

CC	= gcc
LD	= gcc
AS	= gcc
AR	= ar
OBJCOPY	= objcopy
OBJDUMP	= objdump
STRIP = strip

all: Makefile $(PROG) 
#$(PROG).lst

clean:
	@rm -fv $(OFILES) $(PROG).lst $(PROG) $(PROG).exe
	@rm -fv *.png *.plt *.dat

$(PROG): Makefile $(OFILES)
	$(LD) $(OPTIONS) $(LDFLAGS) $(addprefix -L,$(LIBPATH)) -o $@ $(OFILES) $(addprefix -l,$(LIBS))

$(PROG).lst: $(PROG) Makefile
	$(OBJDUMP) -w -D -t -S -r -z $< | sed '/^[0-9,a-f]\{8\} .[ ]*d[f]\?.*$$/d' > $@

%.o : %.c Makefile
	$(CC) $(OPTIONS) $(CFLAGS) $(addprefix -I,$(INCPATH)) $(GTKCFLAGS) -o $@ -c $<

