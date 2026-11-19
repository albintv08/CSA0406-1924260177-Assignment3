#!/bin/sh
set -eu
cd "$(dirname "$0")"
gcc -std=c11 -Wall -Wextra -fPIC -shared crypto.c -o libcrypto_demo.so
gcc -std=c11 -Wall -Wextra bank.c ./libcrypto_demo.so -Wl,-rpath,'$ORIGIN' -o bank_dynamic
gcc -std=c11 -Wall -Wextra bank.c crypto.c -o bank_static_demo
gcc -std=c11 -Wall -Wextra bank_dlopen.c -ldl -o bank_dlopen
gcc -std=c11 -Wall -Wextra show_maps.c -o show_maps
echo "Executable sizes:"
ls -lh bank_dynamic bank_static_demo bank_dlopen
echo "Dynamic dependencies:"
ldd ./bank_dynamic
echo "Run results:"
./bank_static_demo
./bank_dynamic
./bank_dlopen
echo "Memory map (first 30 lines):"
./show_maps | head -n 30
echo "Startup-time sample (repeat on your machine):"
/usr/bin/time -f 'elapsed=%e s max_rss=%M KB' ./bank_static_demo
/usr/bin/time -f 'elapsed=%e s max_rss=%M KB' ./bank_dynamic
