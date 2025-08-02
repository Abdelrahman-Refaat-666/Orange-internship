#include <iostream>

using namespace std;

void printer(int height) {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height - i - 1; j++) {
            cout << ' ';
        }
        for (int j = i; j + 1 > 0; j--) {
            cout << '*';
            cout << ' ';
        }
        cout << endl;
    }
    for (int i = 1; i < height; i++) {
        for (int j = i; j > 0; j--) {
            cout << ' ';
        }
        for (int j = i; j < height; j++) {
            cout << '*';
            cout << ' ';
        }
        cout << endl;
    }
}

int main() {

    int height;
    cin >> height;
    printer(height);
    return 0;
}