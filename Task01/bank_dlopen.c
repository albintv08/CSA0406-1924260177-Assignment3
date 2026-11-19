#include <stdio.h>
#include <dlfcn.h>
typedef int (*encrypt_fn)(int);
int main(void) {
    void *handle = dlopen("./libcrypto_demo.so", RTLD_NOW);
    if (!handle) { fprintf(stderr, "dlopen: %s\n", dlerror()); return 1; }
    dlerror();
    encrypt_fn encrypt = (encrypt_fn)dlsym(handle, "encrypt_value");
    const char *error = dlerror();
    if (error) { fprintf(stderr, "dlsym: %s\n", error); dlclose(handle); return 1; }
    printf("Encrypted value: %d\n", encrypt(1234));
    dlclose(handle);
    return 0;
}
