#!/bin/bash

dd if=/dev/random of=./0 bs=1 count=32 2>/dev/null 

cp 0 PROTECT1

./safemove.sh PROTECT1 2

{ cmp -s 0 2 && [ -f "PROTECT1" ]; }

exit_code=$?

rm -f 0 PROTECT1 2

exit $exit_code