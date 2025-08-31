#include <eqs.h>



int main() {

    int num_of_eqs;
    string equation;
    cout << "Enter the number of equations: ";
    cin >> num_of_eqs;
    Eqs parsed_equation[num_of_eqs];
    for (int i = 0; i < num_of_eqs; i++) {
        cout << "Enter Equation " << i << " : ";
        cin >> equation;
        equation = move_right_to_left(equation);
        parsed_equation[i] = parse(equation);
        parsed_equation[i] = merge_variables(parsed_equation[i]);
        parsed_equation[i].equation = equation;
        parsed_equation[i] = sort_attributes(parsed_equation[i]);
        parsed_equation[i].equation = Form_equation(parsed_equation[i]);
    }
    string input;
    string command;
    string num1;
    string num2;
    while (1) {
        int spaces_count = 0;
        getline(cin, input);
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == ' ') {
                spaces_count++;
            }
        }


        if (spaces_count == 0) {
            command = input.substr(0);
        }
        else if (spaces_count == 1) {
            command = input.substr(0, input.find(" "));
            num1 = input.substr(input.find(" ") + 1);
        }
        else if (spaces_count == 2) {
            command = input.substr(0, input.find(" "));
            num1 = input.substr(input.find(" ") + 1, input.rfind(" "));
            num2 = input.substr(input.rfind(" ") + 1);
        }

        if (command == "exit") {
            break;
        }
        else if (command == "num_vars") {
            print_var(parsed_equation[stoi(num1)].variables_count);
        }
        else if (command == "equation") {
            print_eq(parsed_equation[stoi(num1)].equation);
        }
        else if (command == "column") {
            cout << num1;
            print_column(num1);
        }
        else if (command == "add") {
            string eq_sum = add(parsed_equation, stoi(num1), stoi(num2));
            cout << "The sum = " << eq_sum << endl;
        }

    }


    return 0;
}