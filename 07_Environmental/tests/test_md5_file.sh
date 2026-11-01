#!/bin/bash

BINARY="../src/rhasher"
TEST_FILE="/etc/passwd"

EXPECTED=$(md5sum "$TEST_FILE" | cut -d' ' -f1 | tr '[:lower:]' '[:upper:]')

echo "EXPECTED: $EXPECTED"

RESULT=$(echo "MD5 $TEST_FILE" | $BINARY)

echo "RESULT: $RESULT"

if [[ "$RESULT" == *"$EXPECTED"* ]]; then
  exit 0
else
  exit 1
fi