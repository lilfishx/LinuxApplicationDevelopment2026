#!/bin/bash

BINARY="../src/rhasher"
TEST_STR="123"

EXPECTED=$(echo -n "$TEST_STR" | md5sum | cut -d' ' -f1 | tr '[:lower:]' '[:upper:]')

echo "EXPECTED: $EXPECTED"

RESULT=$(echo "MD5 \"$TEST_STR" | $BINARY)

echo "RESULT: $RESULT"

if [[ "$RESULT" == *"$EXPECTED"* ]]; then
  exit 0
else
  exit 1
fi