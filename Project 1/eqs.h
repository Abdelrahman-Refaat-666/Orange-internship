#ifndef EQS_H
#define EQS_H

#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

// #define PRINT        // uncomment to see the output of every function (for debugging)

#define MAX_EQS 100     // max number of equations (and variables)
#define MAX_TERMS 200   // max number of terms in one equation (both sides)

struct Eqs {

    string equation;
    string terms[MAX_TERMS];
    string variables[MAX_TERMS];
    double coeffecients[MAX_TERMS];
    int empty[MAX_TERMS];
    double absolute_value = 0;
    int term_count = 0;
    int variables_count = 0;
};

// string num_to_str(double num);
// string clean_equation(string equation);
// bool check_equation(string equation);
// string move_right_to_left(string equation);
// Eqs parse(string equation);
// Eqs merge_variables(Eqs eqs);
// bool is_before(string var_one, string var_two);
// Eqs sort_attributes(Eqs eqs);
// string Form_equation(Eqs eqs);
// Eqs read_equation(string equation);
// double get_coeffecient(Eqs* eqs, string variable);
// int get_all_variables(Eqs* eqs, int num_of_eqs, string all_vars[]);
// void print_eq(string equation);
// void print_var(int var_count);
// void print_column(Eqs* eqs, int num_of_eqs, string variable);
// Eqs combine(Eqs eq_one, Eqs eq_two, double factor);
// string add(Eqs* eqs, int eq_one, int eq_two);
// string subtract(Eqs* eqs, int eq_one, int eq_two);
// string substitute(Eqs* eqs, string variable, int eq_one, int eq_two);
// int build_matrix(Eqs* eqs, int num_of_eqs, double D[][MAX_EQS], string replaced_var);
// void print_matrix(double D[][MAX_EQS], int rows, int cols);
// double determinant(double D[][MAX_EQS], int size);
// void solve(Eqs* eqs, int num_of_eqs);


// prints 3 instead of 3.000000 and 2.5 instead of 2.500000
string num_to_str(double num) {

    if (fabs(num - round(num)) < 0.000001) {
        return to_string((long long)round(num));
    }
    string number = to_string(num);
    while (number[number.length() - 1] == '0') {
        number.erase(number.length() - 1);
    }
    return number;
}


// removes spaces and * so 2 * x1 + 3x2 = 5 becomes 2x1+3x2=5
string clean_equation(string equation) {

    string cleaned = "";
    for (int i = 0; i < equation.length(); i++) {
        if (equation[i] != ' ' && equation[i] != '*' && equation[i] != '\r' && equation[i] != '\t') {
            cleaned += equation[i];
        }
    }
    return cleaned;
}


bool check_equation(string equation) {

    int equal_count = 0;
    for (int i = 0; i < equation.length(); i++) {
        if (equation[i] == '=') {
            equal_count++;
        }
        else if (!isalnum(equation[i]) && equation[i] != '+' && equation[i] != '-' && equation[i] != '.') {
            return false;
        }
    }
    if (equal_count != 1) {
        return false;
    }
    if (equation[0] == '=' || equation[equation.length() - 1] == '=') {
        return false;
    }
    return true;
}


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
    else if (right_side[0] == '+') {
        right_side[0] = '-';
    }
    else {
        right_side.insert(0,"-");
    }
    equation = left_side.append(right_side);
    equation.append("=0");

    // any variable without a number before it gets a 1 (x1 -> 1x1)
    if (isalpha(equation[0])) {
        equation.insert(0, "1");
    }
    for (int i = 1; i < equation.length() - 1; i++) {
        if ((equation[i-1] == '-' || equation[i-1] == '+') && isalpha(equation[i])) {
            equation.insert(i, "1");
        }
    }


    #ifdef PRINT
        cout << endl << "Move right to left function: " << endl << equation << "\n\n\n\n";
    #endif


    return equation;
}


Eqs parse(string equation) {

    Eqs eqs;
    eqs.equation = equation;
    for (int i = 1; i < eqs.equation.length(); i++) {
        if (eqs.equation[i] == '+' || eqs.equation[i] == '-' || eqs.equation[i] == '=') {
            if (eqs.term_count == MAX_TERMS) {
                cout << "Too many terms, only the first " << MAX_TERMS << " are taken" << endl;
                break;
            }
            eqs.terms[eqs.term_count] = eqs.equation.substr(0, i);
            eqs.equation.erase(0,i);
            i = 0;
            eqs.term_count++;
        }
    }
    eqs.equation = equation;


    #ifdef PRINT
        cout << "Parse function: " << endl ;
        for (int i = 0; i < eqs.term_count; i++) {
        cout << "term " << i << " = " << eqs.terms[i] << endl;
        }
    #endif


    for (int i = 0; i < eqs.term_count; i++) {
        int letter_index = -1;
        for (int j = 0; j < eqs.terms[i].length(); j++) {
            if (isalpha(eqs.terms[i][j])) {
                letter_index = j;
                break;
            }
        }
        if (letter_index == -1) {       // no letters so it's just a number
            eqs.absolute_value -= atof(eqs.terms[i].c_str());
            eqs.coeffecients[i] = 0;
            eqs.empty[i] = 1;
        }
        else {
            eqs.coeffecients[i] = atof(eqs.terms[i].substr(0, letter_index).c_str());
            eqs.variables[i] = eqs.terms[i].substr(letter_index);
            eqs.empty[i] = 0;
        }
    }


    #ifdef PRINT
        cout << "Term count = " << eqs.term_count << "\t\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.term_count; i++) {
            if (eqs.empty[i] == 0) {
                    cout << "Variablle " << i << " = " << eqs.variables[i] << "\t\t";
                    cout << "coeffecient " << i << " = " << eqs.coeffecients[i] << endl;
            }
        }
    #endif


    return eqs;
}


// puts the same variables together (x1+2x1 -> 3x1) and removes the empty places
Eqs merge_variables(Eqs eqs) {

    string var[MAX_TERMS];
    double coeff[MAX_TERMS];
    int counter = 0;
    for (int i = 0; i < eqs.term_count; i++) {
        if (eqs.empty[i] == 1) {
            continue;
        }
        bool found = false;
        for (int j = 0; j < counter; j++) {
            if (var[j] == eqs.variables[i]) {
                coeff[j] += eqs.coeffecients[i];
                found = true;
                break;
            }
        }
        if (!found) {
            var[counter] = eqs.variables[i];
            coeff[counter] = eqs.coeffecients[i];
            counter++;
        }
    }
    eqs.variables_count = 0;
    for (int i = 0; i < counter; i++) {
        if (fabs(coeff[i]) > 0.000001) {      // x1-x1 = 0 so it's removed
            eqs.variables[eqs.variables_count] = var[i];
            eqs.coeffecients[eqs.variables_count] = coeff[i];
            eqs.empty[eqs.variables_count] = 0;
            eqs.variables_count++;
        }
    }


    #ifdef PRINT
        cout << "\n\n\n" << "Merge function: " << endl << "Term count = " << eqs.term_count << "\t\t\t";
        cout << "Variable count = " << eqs.variables_count << "\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.variables_count; i++) {
                    cout << "Variablle " << i << " = " << eqs.variables[i] << "\t\t" << "coeffecient " << i << " = " << eqs.coeffecients[i] << endl;
            }
    #endif


    return eqs;
}


// x2 comes before x10 so the shorter name comes first, and if they have the same length then alphabetical
bool is_before(string var_one, string var_two) {

    if (var_one.length() != var_two.length()) {
        return var_one.length() < var_two.length();
    }
    return strcmp(var_one.c_str(), var_two.c_str()) < 0;
}


Eqs sort_attributes(Eqs eqs) {

    double temp = 0;
    int min;
    for (int i = 0; i < eqs.variables_count; i++) {
        min = i;
        for (int j = i; j < eqs.variables_count; j++) {
            if (is_before(eqs.variables[j], eqs.variables[min])) {
                min = j;
            }
        }
        eqs.variables[i].swap(eqs.variables[min]);
        temp = eqs.coeffecients[i];
        eqs.coeffecients[i] = eqs.coeffecients[min];
        eqs.coeffecients[min] = temp;
    }


    #ifdef PRINT
        cout << "\n\n\n" << "Sort function: " << endl << "Term count = " << eqs.term_count << "\t\t\t";
        cout << "Variable count = " << eqs.variables_count << "\t\t" << "Absolute value = " << eqs.absolute_value << endl;
        for (int i = 0; i < eqs.variables_count; i++) {
                    cout << "Variablle " << i << " = " << eqs.variables[i] << "\t\t" << "coeffecient " << i << " = " << eqs.coeffecients[i] << endl;
            }
    #endif


    return eqs;
}


string Form_equation(Eqs eqs) {

    string equation = "";
    for (int i = 0; i < eqs.variables_count; i++) {
        if (eqs.coeffecients[i] > 0 && i != 0) {
            equation.append("+");
        }
        if (fabs(eqs.coeffecients[i] + 1) < 0.000001) {
            equation.append("-");
        }
        else if (fabs(eqs.coeffecients[i] - 1) > 0.000001) {
            equation.append(num_to_str(eqs.coeffecients[i]));
        }
        equation.append(eqs.variables[i]);
    }
    if (eqs.variables_count == 0) {
        equation.append("0");
    }
    equation.append("=");
    equation.append(num_to_str(eqs.absolute_value));


    #ifdef PRINT
        cout << endl << "Form equation function: " << endl << equation << "\n\n\n\n";
    #endif


    return equation;
}


// does all the steps on the equation the user entered
Eqs read_equation(string equation) {

    equation = move_right_to_left(equation);
    Eqs eqs = parse(equation);
    eqs = merge_variables(eqs);
    eqs = sort_attributes(eqs);
    eqs.equation = Form_equation(eqs);
    return eqs;
}


double get_coeffecient(Eqs* eqs, string variable) {

    for (int i = 0; i < eqs->variables_count; i++) {
        if (eqs->variables[i] == variable) {
            return eqs->coeffecients[i];
        }
    }
    return 0;
}


// collects every variable in all the equations without repeating and sorts them
int get_all_variables(Eqs* eqs, int num_of_eqs, string all_vars[]) {

    int count = 0;
    for (int i = 0; i < num_of_eqs; i++) {
        for (int j = 0; j < eqs[i].variables_count; j++) {
            bool found = false;
            for (int k = 0; k < count; k++) {
                if (all_vars[k] == eqs[i].variables[j]) {
                    found = true;
                    break;
                }
            }
            if (!found && count < MAX_TERMS) {
                all_vars[count] = eqs[i].variables[j];
                count++;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int min = i;
        for (int j = i; j < count; j++) {
            if (is_before(all_vars[j], all_vars[min])) {
                min = j;
            }
        }
        all_vars[i].swap(all_vars[min]);
    }
    return count;
}


void print_eq(string equation) {

    cout << equation << endl;
}

void print_var(int var_count) {

    cout << var_count << endl;
}

void print_column(Eqs* eqs, int num_of_eqs, string variable) {

    for (int i = 0; i < num_of_eqs; i++) {
        cout << num_to_str(get_coeffecient(&eqs[i], variable)) << endl;
    }
}


// returns eq_one + factor * eq_two
// add is factor = 1, subtract is factor = -1 and substitute uses it too
Eqs combine(Eqs eq_one, Eqs eq_two, double factor) {

    Eqs temp;
    temp.term_count = 0;
    for (int i = 0; i < eq_one.variables_count; i++) {
        temp.variables[temp.term_count] = eq_one.variables[i];
        temp.coeffecients[temp.term_count] = eq_one.coeffecients[i];
        temp.empty[temp.term_count] = 0;
        temp.term_count++;
    }
    for (int i = 0; i < eq_two.variables_count && temp.term_count < MAX_TERMS; i++) {
        temp.variables[temp.term_count] = eq_two.variables[i];
        temp.coeffecients[temp.term_count] = factor * eq_two.coeffecients[i];
        temp.empty[temp.term_count] = 0;
        temp.term_count++;
    }
    temp.absolute_value = eq_one.absolute_value + factor * eq_two.absolute_value;


    #ifdef PRINT
    cout << "\n\n\n" << "combine function: (factor = " << factor << ")" << endl << "Term count = " << temp.term_count << "\t\t\t";
    cout << "Absolute value = " << temp.absolute_value << endl;
    for (int i = 0; i < temp.term_count; i++) {
            cout << "Variablle " << i << " = " << temp.variables[i] << "\t\t" << "coeffecient " << i << " = " << temp.coeffecients[i] << endl;
    }
    #endif


    temp = merge_variables(temp);
    temp = sort_attributes(temp);
    temp.equation = Form_equation(temp);
    return temp;
}

string add(Eqs* eqs, int eq_one, int eq_two) {

    return combine(eqs[eq_one], eqs[eq_two], 1).equation;
}

string subtract(Eqs* eqs, int eq_one, int eq_two) {

    return combine(eqs[eq_one], eqs[eq_two], -1).equation;
}

// takes the variable from eq_two and puts it in eq_one
// ex: x2 in eq_two = (absolute - other terms) / coeffecient of x2
// which is the same as eq_one - (c1 / c2) * eq_two
string substitute(Eqs* eqs, string variable, int eq_one, int eq_two) {

    double c1 = get_coeffecient(&eqs[eq_one], variable);
    double c2 = get_coeffecient(&eqs[eq_two], variable);
    if (c2 == 0) {
        return "";
    }
    return combine(eqs[eq_one], eqs[eq_two], -c1 / c2).equation;
}


// fills D with the coeffecients, every row is an equation and every column is a variable
// if replaced_var is not empty its column is replaced with the absolute values (for Cramer's rule)
// returns the number of columns
int build_matrix(Eqs* eqs, int num_of_eqs, double D[][MAX_EQS], string replaced_var) {

    string all_vars[MAX_TERMS];
    int vars_count = get_all_variables(eqs, num_of_eqs, all_vars);
    if (vars_count > MAX_EQS) {
        vars_count = MAX_EQS;
    }
    for (int i = 0; i < num_of_eqs; i++) {
        for (int j = 0; j < vars_count; j++) {
            if (all_vars[j] == replaced_var) {
                D[i][j] = eqs[i].absolute_value;
            }
            else {
                D[i][j] = get_coeffecient(&eqs[i], all_vars[j]);
            }
        }
    }
    return vars_count;
}

void print_matrix(double D[][MAX_EQS], int rows, int cols) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << num_to_str(D[i][j]);
            if (j != cols - 1) {
                cout << "\t";
            }
        }
        cout << endl;
    }
}


// I used gaussian elimination here because the normal way (cofactors) takes forever with 100 equations
// make the matrix upper triangular then the determinant = multiplication of the diagonal
// every time two rows are swapped the sign changes
double determinant(double D[][MAX_EQS], int size) {

    static double m[MAX_EQS][MAX_EQS];      // static so it doesn't fill the stack
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            m[i][j] = D[i][j];
        }
    }
    double det = 1;
    for (int col = 0; col < size; col++) {
        int pivot = col;
        for (int row = col + 1; row < size; row++) {
            if (fabs(m[row][col]) > fabs(m[pivot][col])) {
                pivot = row;
            }
        }
        if (fabs(m[pivot][col]) < 0.000000001) {
            return 0;
        }
        if (pivot != col) {
            for (int k = 0; k < size; k++) {
                double temp = m[col][k];
                m[col][k] = m[pivot][k];
                m[pivot][k] = temp;
            }
            det = -det;
        }
        det *= m[col][col];
        for (int row = col + 1; row < size; row++) {
            double factor = m[row][col] / m[col][col];
            for (int k = col; k < size; k++) {
                m[row][k] -= factor * m[col][k];
            }
        }
    }


    #ifdef PRINT
        cout << "Determinant function: size = " << size << "\t\tdet = " << det << endl;
    #endif


    return det;
}


// cramer's rule: x = D_x / D
void solve(Eqs* eqs, int num_of_eqs) {

    static double D[MAX_EQS][MAX_EQS];
    static double D_x[MAX_EQS][MAX_EQS];
    string all_vars[MAX_TERMS];
    int vars_count = get_all_variables(eqs, num_of_eqs, all_vars);
    if (vars_count != num_of_eqs) {
        cout << "No Solution" << endl;
        return;
    }
    build_matrix(eqs, num_of_eqs, D, "");
    double D_value = determinant(D, num_of_eqs);
    if (fabs(D_value) < 0.000000001) {
        cout << "No Solution" << endl;
        return;
    }
    for (int i = 0; i < vars_count; i++) {
        build_matrix(eqs, num_of_eqs, D_x, all_vars[i]);
        double answer = determinant(D_x, num_of_eqs) / D_value;
        cout << all_vars[i] << "=" << num_to_str(answer) << endl;
    }
}

#endif
