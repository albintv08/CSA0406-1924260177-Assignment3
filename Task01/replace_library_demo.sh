#!/bin/sh
set -eu
cd "$(dirname "$0")"
gcc -fPIC -shared crypto.c -o libcrypto_demo.so
gcc -Wall -Wextra bank.c ./libcrypto_demo.so -Wl,-rpath,'$ORIGIN' -o bank_dynamic
echo "Before library update:"
./bank_dynamic
cp libcrypto_demo.so libcrypto_demo.old.so
cat > crypto_update.c <<'SRC'
int encrypt_value(int value) { return value ^ 0x1234; }
SRC
gcc -fPIC -shared crypto_update.c -o libcrypto_demo.so
echo "After replacing shared object without relinking application:"
./bank_dynamic
mv libcrypto_demo.old.so libcrypto_demo.so
rm -f crypto_update.c
