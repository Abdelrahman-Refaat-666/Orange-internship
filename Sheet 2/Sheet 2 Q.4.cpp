#include <iostream>

using namespace std;

void check_case(char* input) {

    if (*input >= 'A' && *input <= 'Z') {
        *input = *input + ('a' - 'A');
    }
}

void print(char input) {

    switch (input) {
        case 'w':
            cout << "Move up";
            break;
        case 's':
            cout << "Move down";
            break;
        case 'd':
            cout << "Move right";
            break;
        case 'a':
            cout << "Move left";
            break;
        case 'k':
        case 'j':
            cout << "Kick the ball";
            break;
        case 'p':
            cout << "Pass the ball";
            break;
        case 'o':
            cout << "Over the ball";
            break;
    }
}

int main() {

    char input;
    cin >> input;
    check_case(&input);
    print(input);
    return 0;
}