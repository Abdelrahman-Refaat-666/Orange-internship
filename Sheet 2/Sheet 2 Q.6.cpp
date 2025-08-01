#include <iostream>

using namespace std;

void calc (int num1, int num2, int num3, int* max, int* min) {
    *max = num1 > num2? (num1 > num3? num1 : num3) : (num2 > num3? num2 : num3);
    *min = num1 < num2? (num1 < num3? num1 : num3) : (num2 < num3? num2 : num3);
}

int main() {

    struct Num {
        int num1;
        int num2;
        int num3;
        int max;
        int min;
    };
    Num num;
    cin >> num.num1 >> num.num2 >> num.num3;
    calc(num.num1, num.num2, num.num3, &num.max, &num.min);
    cout << num.min << endl << num.max;
    return 0;
}