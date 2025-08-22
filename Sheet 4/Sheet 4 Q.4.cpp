#include <iostream>
#include <string.h>

using namespace std;



int main() {

    string string1, string2;
    int count = 0;
    cout << "What's the first string? ";
    getline(cin, string1);
    cout << "What's the second string? ";
    getline(cin, string2);
    int len1 = string1.length();
    int len2 = string2.length();
    for (int i = 0; i < len2; i++) {
        if (string1 == string2.substr(i, len1) && i <= len2 - len1) {
            count++;
        }
    }
    cout << count;
    return 0;
}