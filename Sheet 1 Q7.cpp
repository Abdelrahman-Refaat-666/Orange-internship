#include <iostream>
#include <string.h>

using namespace std;

int main() {
    double dollars, quarters, dimes, nickles, cents, change, sum;
    cin >> dollars >> quarters >> dimes >> nickles >> cents;
    dollars = dollars + (quarters * 25 + dimes * 10 + nickles * 5 + cents) / 100;
    change = (quarters * 25 + dimes * 10 + nickles * 5 + cents) % 100.0;
    sum = dollars + change;
    cout << sum;

    return 0;
} 

