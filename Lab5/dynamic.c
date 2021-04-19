#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define check(VALUE, MSG, BADVAL) if (VALUE == BADVAL) { perror(MSG); exit(1); }

int main(){
    char* libs[] = {"./liblib1.so", "./liblib2.so"};
    int lib = 0;
    float (*SinIntegral)(float, float,float) = NULL;
    int (*GCF)(int, int) = NULL;

    void* handle = dlopen(libs[lib], RTLD_NOW);
    check(handle,dlerror(),NULL);

    int command;
    float a,b,c;
    int g,h;
    while((printf("> ") && fflush(stdout)) || scanf("%d", &command) > 0){
        if(command == 0){
            if (dlclose(handle) != 0) {
                perror(dlerror());
                exit(1);
            }
            lib = (lib + 1) % 2;
            if(lib == 0){
                printf("Now im using lib1\n");
                fflush(stdout);
            }
            else{
                printf("Now im using lib2\n");
                fflush(stdout);
            }
            handle = dlopen(libs[lib], RTLD_NOW);
            check(handle, dlerror(), NULL);
        }

        else if(command == 1){
            printf("Enter a,b,c\n>> ");
            fflush(stdout);
            if(scanf("%f %f %f", &a, &b, &c) != 3){
                perror("invalid arguments");
                exit(1);
            }

            SinIntegral = dlsym(handle, "SinIntegral");
            check(SinIntegral,dlerror(),NULL);
            printf("Integrall: %f\n", (*SinIntegral)(a,b,c));
            fflush(stdout);
        }
        else if(command == 2){
            printf("Enter your numbers.\n>> ");
            scanf("%d %d", &g, &h );
            fflush(stdout);

            GCF = dlsym(handle, "GCF");
            check(GCF, dlerror(), NULL);

            printf("GCF is: %d\n", (*GCF)(g,h));
            fflush(stdout);
        }
    }

    if (dlclose(handle) != 0) {
        perror(dlerror());
        exit(1);
    }

    return 0;
}