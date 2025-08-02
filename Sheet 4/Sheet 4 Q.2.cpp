#include <iostream>

using namespace std;



int main() {

    float num[10];
    for (int i = 0; i < 10; i++) {
        cin >> num[i];
    }
    float maximum = num[0], minimum = num[0], average = 0, sum = 0;
    for (int i = 0; i < 10; i++) {
        if (num[i] > maximum) {
            maximum = num[i];
        }
        if (num[i] < minimum) { 
            minimum = num[i];
        }
        sum += num[i];
    }
    average = sum / 10;
    cout << maximum << endl << minimum << endl << average;
    return 0;
}