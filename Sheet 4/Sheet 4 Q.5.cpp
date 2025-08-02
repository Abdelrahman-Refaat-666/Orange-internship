#include <iostream>

using namespace std;

void sort(int* num, int* asc, int* des) {
    int buffer = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (*(num + j) > num[buffer]) {
                buffer = j;
            }
        }
        *(des + i) = *(num + buffer);
        *(num + buffer) = 0;
        buffer = 0;
    }
    for (int i = 0; i < 15; i++) {
        *(asc + i) = des[14 - i];
    }
}

int main() {

    int nums[15];
    int asc[15];
    int des[15];
    for (int i = 0; i < 15; i++) {
        cin >> nums[i];
    }
    sort(nums, asc, des);
    for (int i = 0; i < 15; i++) {
        cout << des[i] << '\t';
    }
    cout << endl;
    for (int i = 0; i < 15; i++) {
        cout << asc[i] << '\t';
    }
    return 0;
}