#include <iostream>

using namespace std;

bool check(int year){
    if(((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0 ) {
        return true;
    }
    return false;
}

int main() {

    int year;
    cin >> year;
    if(check(year)) {
        cout << "The year " << year << " is a leap year";
        return 0;
    }
    cout << "The year " << year << " is NOT a leap year";
    return 0;
}