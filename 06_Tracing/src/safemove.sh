#!/bin/bash

LD_PRELOAD=./protect.so ./move "$@"