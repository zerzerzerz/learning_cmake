#include "subdir1/lib1.h"
#include <iostream>

Person::Person(){

}

Person::~Person(){

}

void Person::sayHello(){
    std::cout << "Hello!" << std::endl;
}

void Person::sayGoodbye(){
    std::cout << "Goodbye!" << std::endl;
}

