#!/bin/sh
set -eu
sleep 30 &
PID=$!
trap 'kill "$PID" 2>/dev/null || true' EXIT
echo "PID=$PID"
echo "Linux process memory mappings:"
cat "/proc/$PID/maps"
wait "$PID"
