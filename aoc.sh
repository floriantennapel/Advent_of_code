#!/bin/bash

DIR=$(pwd)
BASE=$(basename "$DIR")
PARENT=$(dirname "$DIR")
PARENT_DIR=$(basename "$PARENT")

if [[ $BASE =~ day([0-9]+) ]]; then
  DAY=${BASH_REMATCH[1]}
else
  echo "invalid directory name: $BASE"
  exit 1
fi

if [ $DAY -lt 1 ] || [ $DAY -gt 25 ]; then
  echo "invalid argument"
  exit 1
fi

PATH_TO_AOC=""

if [ ! -f "in" ]; then
  node "$PATH_TO_AOC/aoc_get.js" $DAY $PARENT_DIR > "in"
  head -n -1 "in" > "tmp"
  mv "tmp" "in"
fi

if [ -f "sol.py" ]; then
    python "sol.py" < "in"
elif [ -f "sol.cpp" ]; then
    g++ "sol.cpp" && ./a.out < "in"
elif [ -f "sol.c" ]; then
    gcc "sol.c" && ./a.out < "in"
else
    echo "unknown language"
fi
