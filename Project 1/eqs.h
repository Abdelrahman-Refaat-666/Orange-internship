#ifndef EQS_H
#define EQS_H

#include <iostream>
#include <string.h>

#define PRINT

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

string move_right_to_left(string equation);
Eqs parse(string equation);
Eqs merge_variables(Eqs eqs);
Eqs sort_attributes(Eqs eqs);
string Form_equation(Eqs eqs);
void print_eq(string equation);
void print_var(int var_count);
void print_column(string variable);
string add(Eqs* eqs, int eq_one, int eq_two);
int* solve(Eqs* parsed_equations, int num_of_eqs);

#endif EQS_H