#include "functions.h"
#include <math.h>

float SinIntegral( float A, float B, float e){
    double integral = 0;
    for( float dot = A + e; dot < B; dot+=e ){
        integral += (sin( dot ) + sin( dot - e )) / 2 * e;
    }
    return integral;

}
int GCF (int A, int B) {
    while (B) {
        A %= B;
        int temp = A;
        A = B;
        B = temp;

    }
    return A;
}
