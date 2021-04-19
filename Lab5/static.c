#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int command;
    float a,b,c;
    int g,h;
    while(scanf("%d", &command) > 0){
        if(command == 1){
            printf("Enter a,b,c\n>> ");
            if(scanf("%f %f %f", &a, &b, &c) != 3){
                perror("invalid input");
                exit(1);
            }
            printf("Integrall: %f\n", SinIntegral( a, b, c));
            fflush(stdout);
        }

        else if(command == 2){
            printf("Enter your numbers. \n");
            scanf("%d %d", &g, &h );
            fflush(stdout);
            //array initialize
            printf("GCF: %d\n", GCF (g, h));


            printf("\n");
            fflush(stdout);
        }
    }

    return 0;
}
