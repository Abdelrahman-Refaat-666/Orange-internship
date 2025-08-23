#include <iostream>
#include <string.h>

using namespace std;

class complex_numbers {

    public:
        void operator+();
        void operator-();
        void operator*();
        ostream& operator<<();
        operator>>();
    private:
        int real_term;
        int complex_term;
};

int main() {
    
    return 0;
}