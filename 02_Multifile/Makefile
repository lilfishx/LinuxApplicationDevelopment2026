.PHONY: test clean all check
.SECONDARY:

GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o test-*
CFLAGS=-fPIC
CC = cc
AR = ar

all: README prog prog-a prog-so

README: prog
	./$< 2> $@

prog: const.o fun.o prog.o
	$(CC) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) -L. prog.o -l:liboutput_static.a -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. -Wl,-rpath,'$$ORIGIN' prog.o -l:liboutput.so -o $@

liboutput_static.a: fun.o const.o
	$(AR) -rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

fun.o:  outlib.h

prog.o:  outlib.h

test: all-test-prog all-test-prog-a all-test-prog-so check
	@:

all-test-%: test-%-no-arg test-%-one-arg test-%-three-arg
	@:

test-%-no-arg: %
	./$* > $@ 2>&1

test-%-one-arg: %
	./$* hello > $@

test-%-three-arg: %
	./$* one two three > $@

check: check-no-arg check-one-arg check-three-arg

check-%: test-prog-% test-prog-a-% test-prog-so-%
	cmp test-prog-$* test-prog-a-$* && cmp test-prog-a-$* test-prog-so-$*

clean: 
	rm -rf $(GENERATES) $(TRASH)