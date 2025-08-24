#include <iostream>
#include <string.h>

using namespace std;

class complex_numbers {

    public:
        complex_numbers():real{0}, imaginary{0}{}
        complex_numbers(int real, int imaginary):real{real}, imaginary{imaginary}{}
        void set_number(int real, int imaginary) {
            this->real = real;
            this->imaginary = imaginary;
        }
        complex_numbers operator+(complex_numbers input) {
            input.real = input.real + this->real;
            input.imaginary = input.imaginary + this->imaginary;
            return input;
        }
        complex_numbers operator-(complex_numbers input) {
            input.real = input.real - this->real;
            input.imaginary = input.imaginary - this->imaginary;
            return input;
        }
        complex_numbers operator*(complex_numbers input) {
            input.real = input.real * this->real;
            input.imaginary = input.imaginary * this->imaginary;
            return input;
        }
        friend ostream& operator<<(ostream& out, const complex_numbers &input) {
            out << input.real << "+i" << input.imaginary << endl;
            return out;
        }
        friend istream& operator>>(istream& in, complex_numbers &input) {
            in >> input.real;
            in >> input.imaginary;
            return in;
        }
    private:
        int real;
        int imaginary;
};

int main() {
    
    complex_numbers a(10, 20);
    complex_numbers b;
    b.set_number(5,10);
    cout << a << b;
    cout << a + b;
    cin >> a;
    cout << a;
    return 0;
}