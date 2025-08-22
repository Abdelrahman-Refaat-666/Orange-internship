#include <iostream>
#include <string>

using namespace std;

class student {

    public:
        student();
        student(string name);
        void set_name(string name);
        string get_name();
        void add_quiz(int score);
        float get_total_score();
        float get_avg_score();
    private:
        string name;
        float quiz_scores[10];
        float total_quiz_score;
        int quiz_count;
};

student::student() {
    name = {0};
    total_quiz_score = 0;
    quiz_count = 0;
}

student::student(string name) {
    this->name = name;
    total_quiz_score = 0;
    quiz_count = 0;
}
void student::set_name(string name) {
    this->name = name;
}
string student::get_name() {
    return name;
}
void student::add_quiz(int score) {
    quiz_scores[quiz_count] = score;
    quiz_count++;
}
float student::get_total_score() {
    for (int i = 0; i < quiz_count; i++) {
        total_quiz_score += quiz_scores[i];
    }
    return total_quiz_score;
}
float student::get_avg_score() {
    float avg_score = get_total_score() / quiz_count;
    return avg_score;
}

int main() {

    student ahmed("ahmed");
    ahmed.add_quiz(20);
    ahmed.add_quiz(30);
    ahmed.add_quiz(40);
    ahmed.add_quiz(50);
    cout << ahmed.get_name() << endl;
    cout << ahmed.get_total_score() << endl;
    cout << ahmed.get_avg_score() << endl;
    ahmed.set_name("Mohamed");
    cout << ahmed.get_name() << endl;
    return 0;
}