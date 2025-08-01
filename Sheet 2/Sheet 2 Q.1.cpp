#include <iostream>
#include <math.h>

using namespace std;

bool check(float a, float b, float c, float* discriminant){

    *discriminant = pow(b, 2) - 4*a*c;
    if (*discriminant < 0) {
        return true;
    }
    return false;
}

void solver(float a, float b, float c, float discriminant, float* sol1, float* sol2) {

    *sol1 = (-b + sqrt(discriminant)) / 2*a;
    *sol2 = (-b - sqrt(discriminant)) / 2*a;
}

int main() {

    struct equation {
        float a;
        float b;
        float c;
        float discriminant;
        float sol1;
        float sol2;
    };
    equation eq;
    cin >> eq.a >> eq.b >> eq.c;
    if (check(eq.a, eq.b, eq.c, &eq.discriminant)) {
        cout << "There are no solutions.";
        return 1;
    }
    solver(eq.a, eq.b, eq.c, eq.discriminant, &eq.sol1, &eq.sol2);
    cout << eq.sol1 << endl << eq.sol2;
    return 0;
}