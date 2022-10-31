// ./code/square.cpp
#include <iostream>
#include "config.h"
#include "my_func.h"

#ifdef USE_EXTRA_LIB
#include "my_extra_lib.h"
#endif

#ifdef USE_MY_MATH
#include "my_math.h"
#endif

using namespace std;
int main(){
    double b = stod("12.34");
    cout << "This is C++11 feature, b is " << b << endl;


    cout << "Version is " << VERSION_MAJOR << "." << VERSION_MINOR << endl;

    int c = 2;
    int d = 10;
    cout << "Using function from my_func, result of my_sum(" << c << ", " << d << ") is " << my_sum(c,d) << endl;


    #ifdef USE_EXTRA_LIB
        extra_func();
    #else
        cout << "No extra lib" << endl;
    #endif


    #ifdef USE_MY_MATH
        printf("Using my math, power(%d,%d) is %d\n", c, d, power(c,d));
    #else
        cout << "Not use my math" << endl;
    #endif
    
    return 0;
}