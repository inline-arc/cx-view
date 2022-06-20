LOCALBASE = /usr/local
X11BASE = /usr/X11R6
       
CFLAGS = -I$(LOCALBASE)/include -I$(X11BASE)/include
LDFLAGS = -L$(LOCALBASE)/lib -L$(X11BASE)/lib
LDLIBS = -lX11 -lcairo
BIN = see
       
all: $(BIN)
      
output : walla

#editing some shit tempo
CFLAGS := -D_FORTIFY_SOURCE=2 -Wall -W -Wextra -pedantic -Werror -pedantic-errors $(shell imlib2-config --cflags) -O3
LDLIBS := $(shell imlib2-config --libs)
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
MANDIR := $(PREFIX)/share/man/man1
DOCDIR := $(PREFIX)/share/doc/ssocr
DOCS   := AUTHORS COPYING INSTALL THANKS
VERSION := $(shell sed -n 's/^.*VERSION.*\(".*"\).*/\1/p' defines.h)
