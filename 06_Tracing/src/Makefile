.PHONY: test clean install uninstall

CC = gcc
GENERATES = move protect
TRASH = 0 1 2 PROTECT1
VERSION = 1.0.0

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib64

all: move.c protect.c 
	$(CC) move.c -o move
	$(CC) -shared protect.c -o protect.so

tar: 
	tar cvfz move-$(VERSION).tar.gz safemove.sh move.c protect.c Makefile README.md

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp move $(DESTDIR)$(BINDIR)/move
	cp protect.so $(DESTDIR)$(LIBDIR)/protect.so
	cp safemove.sh $(DESTDIR)$(BINDIR)/safemove.sh
	sed -i 's|LD_PRELOAD=\./protect\.so|LD_PRELOAD=$(LIBDIR)/protect.so|g' $(DESTDIR)$(BINDIR)/safemove.sh
	sed -i 's|\./move|move|g' $(DESTDIR)$(BINDIR)/safemove.sh

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/move
	rm -f $(DESTDIR)$(BINDIR)/safemove.sh
	rm -f $(DESTDIR)$(LIBDIR)/protect.so

test: all
	./test.sh

clean-trash:
	rm -f $(TRASH)

clean:
	rm -f $(GENERATES) $(TRASH)
