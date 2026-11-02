#include "eqs.h"


// splits the command to words, ex: "add 1 2" -> "add", "1", "2"
int split_command(string input, string words[]) {

    int count = 0;
    string word = "";
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\r') {
            if (word != "" && count < 4) {
                words[count] = word;
                count++;
            }
            word = "";
        }
        else {
            word += input[i];
        }
    }
    if (word != "" && count < 4) {
        words[count] = word;
        count++;
    }
    return count;
}

// the user writes the equations starting from 1, so this returns the index starting from 0
// returns -1 if the number is wrong
int get_index(string num, int num_of_eqs) {

    if (num.length() == 0 || num.length() > 3) {
        return -1;
    }
    for (int i = 0; i < num.length(); i++) {
        if (!isdigit(num[i])) {
            return -1;
        }
    }
    int index = stoi(num) - 1;
    if (index < 0 || index >= num_of_eqs) {
        return -1;
    }
    return index;
}

void print_help() {

    cout << "Commands:" << endl;
    cout << "num_vars                 -> number of variables in all the equations" << endl;
    cout << "num_vars i               -> number of variables in equation i" << endl;
    cout << "equation i               -> prints equation i" << endl;
    cout << "column x1                -> prints the coeffecients of x1 in all the equations" << endl;
    cout << "add i j                  -> equation i + equation j" << endl;
    cout << "subtract i j             -> equation i - equation j" << endl;
    cout << "substitute x1 i j        -> puts x1 from equation j in equation i" << endl;
    cout << "D                        -> coeffecients matrix" << endl;
    cout << "D x1                     -> coeffecients matrix with x1 column replaced by the absolute values" << endl;
    cout << "D_value                  -> determinant of D" << endl;
    cout << "solve                    -> solves the equations (cramer's rule)" << endl;
    cout << "exit                     -> exit" << endl;
}


int main() {

    int num_of_eqs;
    string equation;
    cout << "Enter the number of equations: ";
    cin >> num_of_eqs;
    while (cin.fail() || num_of_eqs < 1 || num_of_eqs > MAX_EQS) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "The number of equations must be from 1 to " << MAX_EQS << ": ";
        cin >> num_of_eqs;
    }
    getline(cin, equation);     // to take the \n after the number

    Eqs* parsed_equation = new Eqs[num_of_eqs];     // with 100 equations it's too big for the stack
    for (int i = 0; i < num_of_eqs; i++) {
        cout << "Enter Equation " << i + 1 << ": ";
        if (!getline(cin, equation)) {
            cout << "\nInput ended before all equations were entered" << endl;
            delete[] parsed_equation;
            return 0;
        }
        equation = clean_equation(equation);
        if (!check_equation(equation)) {
            cout << "Wrong equation, try again (ex: 2x1+3x2-x3=5)" << endl;
            i--;
            continue;
        }
        parsed_equation[i] = read_equation(equation);
    }

    cout << endl << "The equations after arranging:" << endl;
    for (int i = 0; i < num_of_eqs; i++) {
        cout << i + 1 << ") ";
        print_eq(parsed_equation[i].equation);
    }
    cout << endl << "Type help to see the commands" << endl;

    string input;
    string words[4];
    static double D[MAX_EQS][MAX_EQS];
    while (getline(cin, input)) {

        int words_count = split_command(input, words);
        if (words_count == 0) {
            continue;
        }
        string command = words[0];

        if (command == "exit" || command == "quit") {
            break;
        }
        else if (command == "help") {
            print_help();
        }
        else if (command == "num_vars" && words_count == 1) {
            string all_vars[MAX_TERMS];
            print_var(get_all_variables(parsed_equation, num_of_eqs, all_vars));
        }
        else if (command == "num_vars" && words_count == 2) {
            int index = get_index(words[1], num_of_eqs);
            if (index == -1) {
                cout << "Wrong equation number" << endl;
                continue;
            }
            print_var(parsed_equation[index].variables_count);
        }
        else if (command == "equation" && words_count == 2) {
            int index = get_index(words[1], num_of_eqs);
            if (index == -1) {
                cout << "Wrong equation number" << endl;
                continue;
            }
            print_eq(parsed_equation[index].equation);
        }
        else if (command == "column" && words_count == 2) {
            print_column(parsed_equation, num_of_eqs, words[1]);
        }
        else if ((command == "add" || command == "subtract") && words_count == 3) {
            int index_one = get_index(words[1], num_of_eqs);
            int index_two = get_index(words[2], num_of_eqs);
            if (index_one == -1 || index_two == -1) {
                cout << "Wrong equation number" << endl;
                continue;
            }
            if (command == "add") {
                print_eq(add(parsed_equation, index_one, index_two));
            }
            else {
                print_eq(subtract(parsed_equation, index_one, index_two));
            }
        }
        else if (command == "substitute" && words_count == 4) {
            int index_one = get_index(words[2], num_of_eqs);
            int index_two = get_index(words[3], num_of_eqs);
            if (index_one == -1 || index_two == -1) {
                cout << "Wrong equation number" << endl;
                continue;
            }
            string result = substitute(parsed_equation, words[1], index_one, index_two);
            if (result == "") {
                cout << words[1] << " is not in equation " << index_two + 1 << endl;
            }
            else {
                print_eq(result);
            }
        }
        else if (command == "D" && (words_count == 1 || words_count == 2)) {
            string replaced_var = "";
            if (words_count == 2) {
                replaced_var = words[1];
                string all_vars[MAX_TERMS];
                int vars_count = get_all_variables(parsed_equation, num_of_eqs, all_vars);
                bool found = false;
                for (int i = 0; i < vars_count; i++) {
                    if (all_vars[i] == replaced_var) {
                        found = true;
                    }
                }
                if (!found) {
                    cout << replaced_var << " is not in the equations" << endl;
                    continue;
                }
            }
            int cols = build_matrix(parsed_equation, num_of_eqs, D, replaced_var);
            print_matrix(D, num_of_eqs, cols);
        }
        else if (command == "D_value") {
            int cols = build_matrix(parsed_equation, num_of_eqs, D, "");
            if (cols != num_of_eqs) {
                cout << "D is not a square matrix (" << num_of_eqs << " equations and " << cols << " variables)" << endl;
                continue;
            }
            cout << num_to_str(determinant(D, num_of_eqs)) << endl;
        }
        else if (command == "solve") {
            solve(parsed_equation, num_of_eqs);
        }
        else {
            cout << "Wrong command, type help to see the commands" << endl;
        }
    }

    delete[] parsed_equation;
    return 0;
}
