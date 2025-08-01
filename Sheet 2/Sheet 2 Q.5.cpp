#include <iostream>

using namespace std;

void calc(float num1, float num2, char operation, float* result) {

    switch (operation) {
        case '+':
            *result = num1 + num2;
            break;
        case '-':
            *result = num1 - num2;
            break;
        case '*':
            *result = num1 * num2;
            break;
        case '/':
            *result = num1 / num2;
            break;
    }
}

int main() {

    struct Var {
        float num1 = 0;
        float num2 = 0;
        float result = 0;
        char operation;
    };
    Var var;
    cin >> var.num1 >> var.num2 >> var.operation;
    calc(var.num1, var.num2, var.operation, &var.result);
    cout << var.result;
    return 0;
}