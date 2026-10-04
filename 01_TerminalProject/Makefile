.PHONY: clean install uninstall
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
VERSION = 1.0.0

Show: Show.c
	gcc Show.c -o Show -l ncursesw

install: Show
	mkdir -p $(DESTDIR)$(BINDIR)
	cp Show $(DESTDIR)$(BINDIR)/Show

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/Show

tar:
	tar cvfz Show-$(VERSION).tar.gz Show.c Makefile

clean:
	rm -f Show
