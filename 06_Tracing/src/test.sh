#!/bin/bash

TESTS_DIR="./tests"
failed=0

chmod +x "$TESTS_DIR"/*.sh

for test in "$TESTS_DIR"/*.sh; do
    
  
  # echo "Running $test"

  "$test"
  status=$?

  if [ "$status" -eq 0 ]; then
    echo "Test $test completed"
  else
    echo "Test $test failed"
    ((failed++))
  fi
done

exit $failed