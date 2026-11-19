#!/bin/sh
set -eu
if [ "$#" -ne 1 ]; then echo "Usage: $0 FILE_ON_TEST_DISK" >&2; exit 2; fi
FILE=$1
if [ ! -f "$FILE" ]; then echo "File not found: $FILE" >&2; exit 2; fi
echo "Buffered read benchmark (file: $FILE)"
/usr/bin/time -f 'elapsed=%e s max_rss=%M KB' sh -c 'cat "$1" > /dev/null' sh "$FILE"
echo "For a cold-cache test, use a disposable test machine and an approved cache-clearing procedure; do not change global cache settings on shared systems."
