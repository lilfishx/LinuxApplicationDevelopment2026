.PHONY: test clean

CFLAGS=-O0 -g
CC = gcc
GENERATES = range 
TRASH = tests/test_*_res
ANSWER_FILES = $(wildcard tests/test_*_answer)
TEST_NUMBERS = $(patsubst tests/test_%_answer,test-%,$(ANSWER_FILES))

range: range.c
	$(CC) range.c -o range $(CFLAGS)

test: range $(TEST_NUMBERS)

test-%: range
	gdb --batch --quiet -x tests/test_$*.gdbscript range 2>/dev/null | grep DEBUG | sed -n 's/^DEBUG: \(.*\)$$/\1/p' > tests/test_$*_res
	cmp tests/test_$*_answer tests/test_$*_res 

clean-tests:
	rm -f $(TRASH)

clean:
	rm -f $(GENERATES) $(TRASH)
