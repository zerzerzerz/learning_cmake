#include "my_math.h"

double calc_e(int n){
    double e = 1;
    for(int i = 1; i <= n; i++){
        e *= (1 + 1.0/n);
    }
    return e;
}


double calc_pi(int n){
    double pi = 0;
    for(int i = 0; i < n; i++){
        pi += 1.0/(i*2+1) * (i%2==0?1:-1);
    }
    return pi*4;
}

double calc_sqrt(double n){
    double x = n;
    double y = 1;
    double e = 0.000001;
    while(x - y > e){
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}