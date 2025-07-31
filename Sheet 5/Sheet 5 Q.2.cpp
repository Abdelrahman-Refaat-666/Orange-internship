#include <iostream>

using namespace std;

void storing(int  i, float num, float* arr) {

    arr[i] = num;
}

float avg(int size, float* arr) {

    float result = 0;
    for (int i = 0; i < size; i++) {
        result += arr[i];
    }
    return (result / size);
}

int main() {

    int size1;
    cout << "What's the size of the array? ";
    cin >> size1;
    const int size = size1;
    float arr[size] = {0};
    for (int i = 0; i < size; i++) {
        float num = 0;
        cin >> num;
        storing(i, num, arr);
    }
    
    float result = avg(size, arr);
    cout << result << endl; 

    return 0;
}