#include <iostream>
#include <math.h>

using namespace std;

void calc(float* x, int size, float *avg, float* stan) {

    float s1 = 0, s2 = 0;
    for (int i = 0; i < size; i++) {
        s1 += pow(x[i], 2);
        s2 += x[i];
    }
    *avg = s2 / size;
    s2 = (1 / size) * (pow(s2, 2));
    *stan = sqrt((s1 - s2) / size - 1);

}

int main() {

    int size;
    cout << "How many numebrs?";
    cin >> size;
    float x[size], avg, stan;
    for (int i = 0; i < size; i++) {
        cin >> x[i];
    }
    calc(x, size, &avg, &stan);
    cout << avg << endl << stan;
    return 0;
}