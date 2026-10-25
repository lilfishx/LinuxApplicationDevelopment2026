#!/bin/bash

dd if=/dev/random of=0 bs=1 count=32 2>/dev/null 

cp 0 1

./safemove.sh 1 2

{ cmp -s 0 2 && [ ! -f "1" ]; }

exit_code=$?

rm -f 0 1 2

exit $exit_code