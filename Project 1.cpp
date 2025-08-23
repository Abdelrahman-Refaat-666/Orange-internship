#include <iostream>
#include <string.h>

using namespace std;

#define PRINT

struct Eqs {

    string equation;
    string terms[100];
    string variables[100];
    float coeffecients[100];
    int empty[100];
    float absolute_value = 0;
    int term_count = 0;
    int variables_count = 0;
};


string move_right_to_left(string equation) {

    string left_side = equation.substr(0, equation.find('='));
    string right_side = equation.substr(equation.find('=') + 1);
    for (int i = 1; i < right_side.length(); i++) {
        if (right_side[i] == '+') {
            right_side[i] = '-';
        }
        else if (right_side[i] == '-') {
            right_side[i] = '+';
        }
    }
    if (right_side[0] == '-') {
        right_side[0] = '+';
    }
    else {
        right_side.insert(0,"-");
    }
    equation = left_side.append(right_side);
    equation.append("=0");
        for (int i = 1; i < equation.length() - 1; i++) {
        if ((equation[i-1] == '-' || equation[i-1] == '+') && equation[i] == 'x') {
            equation.insert(i, "1");
        }
    }


    #ifdef PRINT
        cout << endl << "Move fight to left function: " << endl << equation << "\n\n\n\n";
    #endif


    return equation;
}


Eqs parse(string equation) {

    Eqs eqs;
    eqs.equation = equation;
    for (int i = 1; i < eqs.equation.length(); i++) {
        if (eqs.equation[i] == '+' || eqs.equation[i] == '-' || eqs.equation[i] == '=') {
            eqs.terms[eqs.term_count] = eqs.equation.substr(0, i);
            eqs.equation.erase(0,i);
            i = 0;
            eqs.term_count++;
        }
    }
    if (isalpha(eqs.terms[0][0])) {
        string temp = eqs.terms[0];
        eqs.terms[0].clear();
        eqs.terms[0].append("+1");
        eqs.terms[0].append(temp);
    }


    #ifdef PRINT
        cout << "Parse function: " << endl ;
        for (int i = 0; i < eqs.term_count; i++) {
        cout << "term " << i << " = " << eqs.terms[i] << endl;
        }
    #endif


    for (int i = 0; i < eqs.term_count; i++) {
        for (int j = 0; j < eqs.terms[i].length(); j++) {
            if (eqs.terms[i][j] >= 'a' && eqs.terms[i][j] <= 'z') {
                eqs.coeffecients[i] = atof(eqs.terms[i].substr(0, j).c_str());
                eqs.terms[i].erase(0, j);
                eqs.variables[i] = eqs.terms[i];
                break;
            }
        }
        eqs.empty[i] = 0;
    }
    eqs.variables_count = eqs.term_count;
    int absolute;
    for (int i = 0; i < eqs.term_count; i++) {
        absolute = 1;
        for (int j = 0; j < eqs.variables[i].length(); j++) {
            if (eqs.variables[i][j] == 'x') {
                absolute = 0;
                break;
            }
        }
        if (absolute) {
            eqs.absolute_value -= atof(eqs.terms[i].c_str());
            eqs.empty[i] = 1;
            eqs.variables_count--;
        }
        for (int j = 0; j < eqs.term_count; j++) {
            if (eqs.variables[i] == eqs.variables[j] && i != j && eqs.empty[i] != 1) {
                eqs.coeffecients[i] += eqs.coeffecients[j];
                eqs.empty[j] = 1;
                eqs.variables_count--;
            }
        }
    }


    #ifdef PRINT
        int count = 0;
        cout << "Term count = " << eqs.term_count << "\t\t\t";
        cout << "Variable count = " << eqs.variables_count << "\t\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.term_count; i++) {
            if (eqs.empty[i] == 0) {
                    cout << "Variablle " << count << " = " << eqs.variables[i] << "\t\t"; 
                    cout << "coeffecient " << count << " = " << eqs.coeffecients[i] << endl;
                    count++;
            }
        }
    #endif


    return eqs;
}


Eqs merge_variables(Eqs eqs) {

    string var[100];
    float coeff[100];
    int counter = 0;
    for (int i = 0; i < eqs.term_count; i++) {
        if (eqs.empty[i] == 0) {
            var[counter] = eqs.variables[i];
            coeff[counter] = eqs.coeffecients[i];
            eqs.empty[counter] = 0;
            counter++;
        }
    }
    for (int i = 0; i < eqs.variables_count; i++) {
        if (eqs.empty[i] == 0) {
            eqs.variables[i] = var[i];
            eqs.coeffecients[i] = coeff[i];
        }
    }


    #ifdef PRINT
        cout << "\n\n\n" << "Merge function: " << endl << "Term count = " << eqs.term_count << "\t\t\t";
        cout << "Variable count = " << eqs.variables_count << "\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.variables_count; i++) {
                    cout << "Variablle " << i << " = " << eqs.variables[i] << "\t\t" << "coeffecient " << i << " = " << eqs.coeffecients[i] << "\t\t"; 
                    cout << "Empty " << i << " = " << eqs.empty[i] << endl;
            }
    #endif


    return eqs;
}


Eqs sort_attributes(Eqs eqs) {

    int temp = 0;
    int min;
    for (int i = 0; i < eqs.variables_count; i++) {
        min = i;
        for (int j = i; j < eqs.variables_count; j++) {

            if (eqs.variables[min].length() > eqs.variables[j].length()) {
                min = j;                
            }
            else if (eqs.variables[min].length() < eqs.variables[j].length()) {}
            else if (strcmp(eqs.variables[min].c_str(), eqs.variables[j].c_str()) > 0) {
                min = j;                
            }
        }
        eqs.variables[i].swap(eqs.variables[min]);
        temp = eqs.coeffecients[i];
        eqs.coeffecients[i] = eqs.coeffecients[min];
        eqs.coeffecients[min] = temp;
        temp = eqs.empty[i];
        eqs.empty[i] = eqs.empty[min];
        eqs.empty[min] = temp;
        
    }


    #ifdef PRINT
        cout << "\n\n\n" << "Sort function: " << endl << "Term count = " << eqs.term_count << "\t\t\t";
        cout << "Variable count = " << eqs.variables_count << "\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.variables_count; i++) {
                    cout << "Variablle " << i << " = " << eqs.variables[i] << "\t\t" << "coeffecient " << i << " = " << eqs.coeffecients[i] << "\t\t"; 
                    cout << "Empty " << i << " = " << eqs.empty[i] << endl;    
            }
    #endif


    return eqs;
}


string Form_equation(Eqs eqs) {

    string equation = {0};
    for (int i = 0; i < eqs.variables_count; i++) {
        if (eqs.coeffecients[i] > 0) {
            equation.append("+");
        }
        if (eqs.coeffecients[i] != 1) {
            equation.append(to_string((int)eqs.coeffecients[i]));
        }
        equation.append(eqs.variables[i]);
    }
    equation.erase(1, 1);
    equation.append("=");
    equation.append(to_string((int)eqs.absolute_value));
    

    #ifdef PRINT
        cout << endl << "Form equation function: " << endl << equation << "\n\n\n\n";
    #endif


    return equation;
}

void print_eq(string equation) {

    cout << equation << endl;
}

void print_var(int var_count) {
    cout << var_count << endl;
}

void print_column(string variable) {

}

string add(Eqs* eqs, int eq_one, int eq_two) {

    Eqs temp;
    temp.variables_count = 0;
    for (int i = 0; i < eqs[eq_one].variables_count; i++) {
        bool found = false;
        int found_index;
        for (int j = 0; j < eqs[eq_two].variables_count; j++) {
            if (eqs[eq_two].variables[j] == eqs[eq_one].variables[i]) {
                found = true;
                found_index = j;
                break;
            }
        }
        if (found) {
            temp.variables[temp.variables_count] = eqs[eq_one].variables[i];
            temp.coeffecients[temp.variables_count] = eqs[eq_one].coeffecients[i] + eqs[eq_two].coeffecients[found_index];
            temp.empty[temp.variables_count] = 0;
        } 
        else {
            temp.variables[temp.variables_count] = eqs[eq_one].variables[i];
            temp.coeffecients[temp.variables_count] = eqs[eq_one].coeffecients[i];
            temp.empty[temp.variables_count] = 0;
        }
        temp.variables_count++;
    }
    for (int i = 0; i < eqs[eq_two].variables_count; i++) {
        bool found = false;
        for (int j = 0; j < eqs[eq_one].variables_count; j++) {
            if (eqs[eq_two].variables[i] == eqs[eq_one].variables[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            temp.variables[temp.variables_count] = eqs[eq_two].variables[i];
            temp.coeffecients[temp.variables_count] = eqs[eq_two].coeffecients[i];
            temp.empty[temp.variables_count] = 0;
            temp.variables_count++;
        }
    }
    temp.absolute_value = eqs[eq_one].absolute_value + eqs[eq_two].absolute_value;


    #ifdef PRINT
    cout << "\n\n\n" << "add function: " << endl << "Term count = " << temp.variables_count << "\t\t\t";
    cout << "Variable count = " << temp.variables_count << "\t\t" << "Absolute value = " << temp.absolute_value << endl;
    for (int i = 0; i < temp.variables_count; i++) {
            cout << "Variablle " << i << " = " << temp.variables[i] << "\t\t" << "coeffecient " << i << " = " << temp.coeffecients[i] << "\t\t"; 
            cout << "Empty " << i << " = " << temp.empty[i] << endl;    
    }
    #endif


    temp = sort_attributes(temp);
    string equation = Form_equation(temp);
    return equation;
}

int* solve(Eqs* parsed_equations, int num_of_eqs) {

    for (int i = 0; i < num_of_eqs; i++) {
        for (int j = 0; j < num_of_eqs + 1; j++) {
            
        }
    }



    #ifdef PRINT
    
    #endif

}



int main() {

    int num_of_eqs;
    string equation;
    cin >> num_of_eqs;
    Eqs parsed_equation[num_of_eqs];
    for (int i = 0; i < num_of_eqs; i++) {
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