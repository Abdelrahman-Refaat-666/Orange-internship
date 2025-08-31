#include <iostream>
#include <string.h>

using namespace std;

class PERSON {

    public:
        virtual void set_name(string name) {
            this->name = name;
        }
        virtual void set_birthday(int birthday) {
            this->birthday = birthday;
        }
        virtual void print() {
            cout << name << '\t' << birthday << endl;
        }
    protected:
        string name;
        int birthday;
};

class student:public PERSON {

    string major;
    public:
        student() {
            major = "";
        }
        student(string name, int birthday, string major) {
            this->name = name;
            this->birthday = birthday;
            this->major = major;
        }
        void set_major(string major) {
            this->major = major;
        }
        void print() {
            cout << name << '\t' << birthday << '\t' << major << endl;
        }
};

class instructor:public PERSON {

    int salary;
    public:
        instructor() {
            salary = 0;
        }
        instructor(string name, int birthday, int salary) {
            this->name = name;
            this->birthday = birthday;
            this->salary = salary;
        }
        void set_salary(int salary) {
            this->salary = salary;
        }
        void print() {
            cout << name << '\t' << birthday << '\t' << salary << endl;
        }
};

int main() {
    
    student ahmed;
    instructor mohamed;
    ahmed.set_name("ahmed");
    ahmed.set_birthday(2004);
    ahmed.set_major("Engineering");
    mohamed.set_name("mohamed");
    mohamed.set_birthday(1990);
    mohamed.set_salary(30000);
    ahmed.print();
    mohamed.print();
    return 0;
}