#!/bin/bash

dd if=/dev/random of=0 bs=1 count=32 2>/dev/null 

cp 0 1

strace -P 1 -e trace=read -e fault=read:error=EINTR ./move 1 2 2>/dev/null

exit_code=$?

{ [ "$exit_code" -eq 6 ] && [ -f "1" ] && [ ! -f "2" ]; }

exit_code=$?

rm -f 0 1 2

exit $exit_code