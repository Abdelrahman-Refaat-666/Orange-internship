#include <iostream>
#include <string.h>

using namespace std;

int main() {
    double R1, R2, R_series, R_parallel;
    cin >> R1 >> R2;
    R_series = R1 + R2;
    R_parallel = 1 / (1/R1 + 1/R2);
    cout << R_series << endl << R_parallel;
    return 0;
} 

