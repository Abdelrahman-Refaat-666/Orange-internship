#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

string replacer(string input) {

    string output;
    int count = 0;
    int length = strlen(input.c_str());
    string words[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < length; i++) {
        if (input[i] <= '9' && input[i] >= '0' ) {
            int num = input[i] -'0';
            output.append(words[num]);
        }
        else {
            output.push_back(input[i]);
        }
    }
    return output;
}

int main() {

    string input;
    string output;
    getline(cin, input);
    output = replacer(input);
    cout << output;
    return 0;
}