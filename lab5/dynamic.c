#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>

float (*derivative)(float, float);
int (*prime_counter)(int, int);

int dl_error(void* handle) {
    if (!handle){
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(1);
    }
}

void functions_initialization(void* handle) {
    derivative = dlsym(handle, "Derivative");
    prime_counter = dlsym(handle, "PrimeCount");
}   

int main() {
    int command;
    int library_mode = 1;
    void* library_handle; 
    library_handle = dlopen("libdynamic1.so", RTLD_LAZY);
    dl_error(library_handle);
    functions_initialization(library_handle);
    printf("How using library 'libdynamic1.so'\n");
    printf("Select a command:\n0 - change library\n1 - derivative cos(x) function\n2 - number of primes\n");
    while (scanf("%d", &command) != EOF) {
        switch (command) {
            case 0: {
                dlclose(library_handle);
                if (library_mode == 1) {
                    library_mode = 2;
                    library_handle = dlopen("libdynamic2.so", RTLD_LAZY);
                    dl_error(library_handle);
                    functions_initialization(library_handle);
                    printf("Now using library 'libdynamic2.so'\n");
                } else {
                    dlclose(library_handle);
                    library_handle = dlopen("libdynamic1.so", RTLD_LAZY);
                    dl_error(library_handle);
                    library_mode = 1;
                    functions_initialization(library_handle);
                    printf("How using library 'libdynamic1.so'\n");
                }
                break;
            }

            case 1: {
                printf("Enter x and delta_x: ");
                float x, delta_x;
                scanf("%f %f", &x, &delta_x);
                printf("Derivative equals %f\n", (*derivative)(x, delta_x)); 
                printf("\nSelect a command:\n0 - change library\n1 - derivative cos(x) function\n2 - number of primes\n");
                break;
            }

            case 2: {
                printf("Enter natural range [A;B]: ");
                int left_limit, right_limit;
                scanf("%d %d", &left_limit, &right_limit);
                printf("Number of primes: %d\n", (*prime_counter)(left_limit, right_limit));
                printf("\nSelect a command:\n0 - change library\n1 - derivative cos(x) function\n2 - number of primes\n");
                break;
            }

            default: {
                printf("Wrong command! Try again.\n");
                printf("Select a command:\n0 - change library\n1 - derivative cos(x) function\n2 - number of primes\n");
            }
                
        }
    }
    return 0;
}
