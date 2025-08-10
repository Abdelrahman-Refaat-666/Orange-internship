#include <iostream>
#include <string.h>

using namespace std;



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
    eqs.variables_count = eqs.term_count;
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
    return eqs;
}


Eqs merge_variables(Eqs eqs) {

    cout << "variable count = " << eqs.variables_count << endl;
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
    return equation;
}


string add(Eqs* eqs, int eq_one, int eq_two) {

    int length;
    Eqs temp;
    if (eqs[eq_one].variables_count > eqs[eq_two].variables_count) {
        length = eqs[eq_one].variables_count;
    }
    else {
        length = eqs[eq_two].variables_count;
    }
    temp.variables_count = length;
    for (int i = 0; i < length; i++) {
        if (eqs[eq_one].variables[i] == eqs[eq_two].variables[i]) {
            temp.variables[i] = eqs[eq_one].variables[i];
            temp.coeffecients[i] = eqs[eq_one].coeffecients[eq_one] + eqs[eq_two].coeffecients[eq_two];
            temp.empty[i] = 0;
        }
        else {
            temp.variables[i] = eqs[eq_one].variables[i];
            temp.variables[i+1] = eqs[eq_two].variables[i];
            temp.coeffecients[i] = eqs[eq_one].coeffecients[eq_one];
            temp.coeffecients[i+1] = eqs[eq_two].coeffecients[eq_two];
            temp.empty[i] = 0;
            temp.empty[i+1] = 0;
            temp.variables_count++;
        }
    }
    temp.absolute_value = eqs[eq_one].absolute_value + eqs[eq_two].absolute_value;
    temp = sort_attributes(temp);
    string equation = Form_equation(temp);
    return equation;
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
    for (int i = 0; i < parsed_equation[0].variables_count; i++){
        cout << "Variable " << i << "= " << parsed_equation[0].variables[i] << '\t';
        cout << "Empyt " << i << "= " << parsed_equation[0].empty[i] << '\t';
        cout << "coeff " << i << "= " << parsed_equation[0].coeffecients[i] << endl;
    }
    cout << "Parsed equation = " << parsed_equation[0].equation << endl;
    cout << "Absoulute value = " << parsed_equation[0].absolute_value << endl;
    
    return 0;
}