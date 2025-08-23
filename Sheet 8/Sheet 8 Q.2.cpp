#include <iostream>
#include <string.h>

using namespace std;

class Money {

    public:
        Money(): dollars{0}, cents{0}{}

        void add_money(int dollars, int cents) {
            this-> dollars = dollars;
            this-> cents = cents;
        }
        Money operator+(Money in) {
            this->dollars = this->dollars + in.dollars;
            this->cents = this->cents + in.cents;
            return *this;
        }
        Money operator-(Money in) {
            in.dollars = this->dollars - in.dollars;
            in.cents = this->cents - in.cents;
            return in;
        }
        Money operator*(Money in) {
            in.dollars = this->dollars * in.dollars;
            in.cents = this->cents * in.cents;
            return in;
        }
        Money operator/(Money in) {
            in.dollars = this->dollars / in.dollars;
            in.cents = this->cents / in.cents;
            return in;
        }
        friend ostream & operator <<(ostream &out, const Money input) {
            out << input.dollars << " Dollars " << input.cents << " Cents\n";
            return out;
        }
        friend istream & operator >>(istream &in, Money &input) {
            in >> input.dollars >> input.cents;
            return in;
        }
    private:
        int dollars;
        int cents;
};


int main() {
    
    Money m, n;
    m.add_money(10,20);
    cout << m << endl;
    cin >> n;
    cout << m + n << endl;
    return 0;
}