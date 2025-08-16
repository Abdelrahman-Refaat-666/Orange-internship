#include <iostream>
#include <string>

using namespace std;

class Person {

    public:
        Person();
        Person(string pname, int page);
        void get_name();
        void get_age();
    private:
        string name;
        int age;
};

Person::Person() {
    name = "";
    age = 0;
}

Person::Person(string pname, int page) {
    name = pname;
    age = page;
}

void Person::get_name() {

    cout << "name = " << name << endl;
}

void Person::get_age() {

    cout << "age = " << age << endl;
}
