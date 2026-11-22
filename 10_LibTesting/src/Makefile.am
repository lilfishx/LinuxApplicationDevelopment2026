AM_CFLAGS = -std=c99 -pedantic -Wall -Wextra
if COND_GCOV
AM_CFLAGS	+= -O0 -g -fprofile-arcs -ftest-coverage
else
AM_CFLAGS	+= -O3 -g3
endif

lib_LTLIBRARIES = libgrowbuf.la
libgrowbuf_la_SOURCES = growbuf.c
include_HEADERS = growbuf.h

libgrowbuf_la_LDFLAGS = -version-info 1:0:0


gcov:
	gcov -o .libs growbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
