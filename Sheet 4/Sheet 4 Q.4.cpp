#include <iostream>

using namespace std;

int length(char* arr, int size) {
    int count  = 0;
    for (int i = 1; i <= size; i++) {
        if (*(arr + i) == '\0') {
            return count;
        }
        count++;
    }
    return 1;
}

int main() {

    char string1[50] = {0}, string2[500] = {0};
    cout << "What's the first string?";
    cin >> string1;
    cout << "What's the second string?";
    cin >> string2;
    int length1 = length(string1, 50), length2 = length(string2, 500);
    cout << length1 << endl << length2;
    return 0;
}