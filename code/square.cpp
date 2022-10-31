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
    int a;
    double b = stod("12.34");
    cout << "b is " << b << endl;
    cout << "Please enter an int" << endl;
    cin >> a;
    cout << "square of " << a << " is " << a*a << endl;
    cout << "version is " << VERSION_MAJOR << "." << VERSION_MINOR << endl;

    int c = 12;
    int d = 12;
    cout << "result of my_sum(" << c << ", " << d << ") is " << my_sum(c,d) << endl;

    #ifdef USE_EXTRA_LIB
        extra_func();
    #else
        cout << "No extra lib" << endl;
    #endif

    #ifdef USE_MY_MATH
        cout << "Use my math" << " " << power(3,2) << endl;
    #else
        cout << "Not use my math" << endl;
    #endif
    
    return 0;
}