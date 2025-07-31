#include <iostream>

using namespace std;

void calc(int apples, int* dozens, int* left_over) {

    *dozens = apples / 12;
    *left_over = apples % 12;
}

int main() {

    struct bag {
        int apples;
        int dozens;
        int left_over;
    };
    bag box;
    cin >> box.apples;
    calc(box.apples, &box.dozens, &box.left_over);
    cout << box.dozens << endl << box.left_over;
    return 0;
}