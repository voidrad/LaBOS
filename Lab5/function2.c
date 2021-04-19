#include "functions.h"
#include <math.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
float SinIntegral( float A, float B, float e){
    double integral = 0;
    for( float dot = A + e; dot < B; dot+=e ){
        integral += (sin( dot ) + sin( dot - e )) / 2 * e;
    }
    return integral;

}



#define min(a, b) ((a) < (b) ? (a) : (b))

int GCF (int A, int B) {
    for( int i = min ( A, B ); i > 1; i-- ){
        if ( A % i == 0 && B % i == 0 ){
            return i;
        }
    }
    return 1;
}
