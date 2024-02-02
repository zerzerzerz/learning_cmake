#include <iostream>
#include "my_greet.h"
#include "my_math.h"
#include "person.h"
#include "config.h"

using namespace std;

int main(int argc, char *argv[]){
    cout << "Version: " << "v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << endl;
    if(argc != 3){
        cout << "Usage: " << argv[0] << " <name> <age>" << endl;
        return 1;
    }
    greet(argv[1]);

    Student s(argv[1], atoi(argv[2]));
    cout << "Age: " << s.getAge() << endl;

    int n = 0;
    cout << "Please enter an inetger: ";
    cin >> n;
    cout << "e = " << calc_e(n) << endl;
    return 0;
}
