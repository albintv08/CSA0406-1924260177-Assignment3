# Q1 – Linking, Loading and Address Binding

## Source files
- `crypto.c`, `bank.c`: same application using an encryption-library function.
- `bank_dlopen.c`: runtime loading with `dlopen()` and `dlsym()`.
- `show_maps.c`: prints `/proc/self/maps`.
- `build_and_measure.sh`: builds both linking styles, runs them, lists sizes/dependencies and samples startup time/RSS.
- `replace_library_demo.sh`: replaces the shared object without relinking the application.

## Run
```bash
sh build_and_measure.sh
sh replace_library_demo.sh
```
For two process mappings, start two long-running copies and inspect their `/proc/PID/smaps` files. Compare `Shared_Clean` and `Private_Clean` fields; shared-library code pages can be shared when mapped read-only. To test a missing library, temporarily rename `libcrypto_demo.so`, run `./bank_dynamic`, then restore it.

## Evaluation notes
Static linking copies library code into the executable. Dynamic linking resolves a shared object at load time; `dlopen()` defers it until execution requests it. PIC enables relocation of shared code. Measure startup and memory on your own Linux machine and record actual output; do not assume one linking style is always faster.
