#include <iostream>

using namespace std;

void calc(float R1, float R2, float* R_parallel, float* R_series){
    *R_series = R1 + R1;
    *R_parallel =1 / (1/R1 + 1/R2);
}

int main() {

    struct resistor {
        float parallel;
        float series;
    };

    resistor resistors;
    float R1, R2;
    cout << "What are the vales of the first and the second resistores? ";
    cin >> R1 >> R2;
    calc(R1, R2, &resistors.parallel, &resistors.series);
    cout << "In series: " << resistors.series << endl << "In parallel: " << resistors.parallel;
    return 0;
}