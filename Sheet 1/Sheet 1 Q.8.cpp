#include <iostream>
#include <math.h>

using namespace std;

bool check(float m, float n) {

    if (m < n) {
        return 1;
    }
    return 0;
}

void calc(float m, float n, float* a, float* b, float* c) {

    *a = pow(m,2) - pow(n,2);
    *b = 2 * m * n;
    *c = sqrt(pow(*a, 2) + pow(*b, 2));
}

int main() {

    float m, n, a , b, c;
    cout << "Enter m: ";
    cin >> m;
    cout << "Enter n: ";
    cin >> n;
    if (check(m, n)) {
        cout << "M can't be bigger than n";
        return 1;
    }
    struct Triple {
        float a;
        float b;
        float c;
    };
    Triple triple;
    calc(m, n, &a, &b, &c);
    cout << "a = " << a << " b = " << b << " c = " << c;
    return 0;
}