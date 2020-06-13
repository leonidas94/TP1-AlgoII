#include <iostream>
#include <cmath>
#include <string>
#include "stk.h"
//#include "str.h"

static const int precedence_2 = 2;
static const int precedence_3 = 3;
static const int precedence_4 = 4;


void shunting_yard2(stk <string> &, string[], size_t);

int precedence (string token);
bool is_left_parenthesis(string); 
bool is_right_parenthesis(string);
bool is_operator(string);
bool is_left_associative(string);
bool is_function (string);
bool isdigit (string );
void solve_rpn(stk <string> &);