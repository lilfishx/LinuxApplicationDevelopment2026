#!/bin/bash

BINARY="../src/rhasher"
TEST_FILE="/etc/passwd"

EXPECTED=$(sha1sum "$TEST_FILE" | cut -d' ' -f1 | tr '[:lower:]' '[:upper:]')

echo "EXPECTED: $EXPECTED"

RESULT=$(echo "SHA1 $TEST_FILE" | $BINARY)

echo "RESULT: $RESULT"

if [[ "$RESULT" == *"$EXPECTED"* ]]; then
  exit 0
else
  exit 1
fi