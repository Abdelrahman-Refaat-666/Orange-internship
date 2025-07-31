#include <iostream>

using namespace std;

void calc(float dollars, float quarters, float dimes, float nickles, float cents,float* result) {

    *result = dollars + ((quarters * 25 + dimes * 10 + nickles * 5 + cents) / 100);
}

int main() {

    float dollars, quarters, dimes, nickles, cents, result;
    cin >> dollars >> quarters >> dimes >> nickles >> cents;
    calc(dollars, quarters, dimes, nickles, cents, &result);
    cout << result;
    return 0;
}