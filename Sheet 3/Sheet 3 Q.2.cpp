#include <iostream>
#include <string.h>

using namespace std;

void replacer(char output[2000], int length) {

    char input[2000];
    cin.getline >> input;
    int count = 0;
    char words[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < length; i++) {
        if (input[i] <= '9' && input[i] >= '0' ) {
            int num = input[i] -'0';
            for (int j = i; (i - j) < strlen(words[num]); i++) {
                output[i] = words[num][i - j];
            }
        }
        else {
            output[i] = input[count];
        }
        count++;
    }
}

int main() {

    char output[2000] = {0};
    int length = 2000;
    replacer(output, length);
    cout << output;
    return 0;
}