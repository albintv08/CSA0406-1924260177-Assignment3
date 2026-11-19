# Q1 – Linking, Loading and Address Binding

Build:
```bash
gcc -Wall -Wextra -fPIC -shared crypto.c -o libcrypto_demo.so
gcc -Wall -Wextra bank.c ./libcrypto_demo.so -Wl,-rpath,'$ORIGIN' -o bank_dynamic
gcc -Wall -Wextra bank.c crypto.c -o bank_static_demo
gcc -Wall -Wextra bank_dlopen.c -ldl -o bank_dlopen
./bank_dynamic
./bank_static_demo
./bank_dlopen
ls -lh bank_dynamic bank_static_demo
ldd ./bank_dynamic
```

Compare static and dynamic executable sizes, inspect dependencies, and test runtime loading. PIC allows shared-library code to be mapped at different virtual addresses. Capture real output and measurements from your machine; inspect `/proc/<pid>/maps` while the process is alive.
