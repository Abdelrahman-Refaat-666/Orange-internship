#include <iostream>

using namespace std;

void calc(float R1, float R2,float* R_parallel, float* R_series){
    *R_series = R1 + R1;
    *R_parallel =1 / (1/R1 + 1/R2);
}

int main() {

    float R1, R2, R_parallel, R_series;
    cout << "What are the vales of the first and the second resistores? ";
    cin >> R1 >> R2;
    calc(R1, R2, &R_parallel, &R_series);
    cout << "In series: " << R_series << endl << "In parallel: " << R_parallel;
    return 0;
}