#include <iostream>

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



int main() {

    return 0;
}