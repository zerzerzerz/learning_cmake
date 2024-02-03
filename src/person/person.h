#include <string>
using namespace std;

class Student{
    public:
        Student(const string& _name, int _age);
        ~Student();
        void setAge(int age);
        int getAge();
        string getName();
        void setName(const string& name);
        string display();
    private:
        string name;
        int age;
};
