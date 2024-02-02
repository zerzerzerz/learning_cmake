#include "person.h"
#include "my_greet.h"

Student::Student(const string& _name, int _age){
    name = _name;
    age = _age;
    hello(name);
}

Student::~Student(){
    goodbye(name);
}

void Student::setAge(int _age){
    age = _age;
}

int Student::getAge(){
    return age;
}

string Student::getName(){
    return name;
}