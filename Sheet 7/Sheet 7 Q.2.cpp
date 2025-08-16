#include <iostream>
#include <string>

using namespace std;



class Person {

    public:
        Person();
        Person(string pname, int page);
        string get_name();
        int get_age();
    private:
        string name;
        int age;
};



class PEmployee {

    public:
        PEmployee();
        PEmployee(string employee_name, double initial_salary);
        void set_salary(double new_salary);
        void get_salary();
        void get_name();
    private:
        Person person_data;
        double salary;
};



Person::Person() {
    name = "";
    age = 0;
}

Person::Person(string pname, int page) {
    name = pname;
    age = page;
}

string Person::get_name() {

    return name;
}

int Person::get_age() {

    return age;
}

PEmployee::PEmployee() {

    person_data = Person();
    salary = 0;
}

PEmployee::PEmployee(string employee_name, double initial_salary) {

    person_data = Person(employee_name, 0);
    salary = initial_salary;
}

void PEmployee::set_salary(double new_salary) {
    salary = new_salary;
}

void PEmployee::get_salary() {

    cout << "Salary = " << salary << endl;
}

void PEmployee::get_name() {
    cout << "name = " << person_data.get_name() << endl;
}
