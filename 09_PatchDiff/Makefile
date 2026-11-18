.PHONY: all run clean

CC = gcc
CFLAGS = -Wall -Wextra -O2
VERSION = 1.0.0

BASE = maze_v0
V1 = maze_v1
V2 = maze_v2
V3 = maze_v3

GENERATES = $(BASE) $(V1) $(V2) $(V3) $(V1).c $(V2).c $(V3).c

PATCHES = patches/0001-Maze-size-from-command-line.patch \
	patches/0002-Pass-and-wall-chars-from-command-line.patch \
	patches/0003-Seed-from-command-line.patch

all: $(BASE) $(V1) $(V2) $(V3)

$(BASE): maze.c
	$(CC) $(CFLAGS) -o $@ $<

$(V1).c: maze.c $(word 1,$(PATCHES))
	patch -p1 -o $@ maze.c $(word 1,$(PATCHES))

$(V1): $(V1).c
	$(CC) $(CFLAGS) -o $@ $<

$(V2).c: $(V1).c $(word 2,$(PATCHES))
	patch -p1 -o $@ $(V1).c $(word 2,$(PATCHES))

$(V2): $(V2).c
	$(CC) $(CFLAGS) -o $@ $<

$(V3).c: $(V2).c $(word 3,$(PATCHES))
	patch -p1 -o $@ $(V2).c $(word 3,$(PATCHES))

$(V3): $(V3).c
	$(CC) $(CFLAGS) -o $@ $<

tar:
	tar cvfz maze-$(VERSION).tar.gz maze.c Makefile patches

run: all
	./$(BASE)
	./$(V1) 8
	./$(V2) 6 " @"
	./$(V3) 42 ".#" 4

clean:
	rm -f $(BASE) $(V1) $(V2) $(V3) $(V1).c $(V2).c $(V3).c
