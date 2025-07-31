#include <iostream>

using namespace std;

void addarrays(float* arr1, float* arr2, float* arr3, int size) {

    for (int i = 0; i < size; i++) {
        arr3[i] = arr1[i] + arr2[i];
    }
}

int main() {

    const int size = 5;
    float arr1[size] = {1, 2, 3, 4, 5};
    float arr2[size] = {1, 2, 3, 4, 5};
    float arr3[size];
    addarrays(arr1, arr2, arr3, size);
    return 0;
}