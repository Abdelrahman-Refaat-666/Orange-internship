#include <iostream>
#include <string.h>

using namespace std;

void counter(char input[100], int* count) {

    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            *count += 1;
        }
    }
}

int main() {

    char input[100];
    int count = 0;
    cin >> input;
    counter(input, &count);
    cout << count;
    return 0;
}