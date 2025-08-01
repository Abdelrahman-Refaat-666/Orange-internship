#include <iostream>

using namespace std;



int main() {
    
    int month;
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    cin >> month;
    cout << days[month] << " days.";
    return 0;
}