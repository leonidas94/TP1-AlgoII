#include <iostream>
#include "stk.h"
#include "str.h"

static const int precedence_2 = 2;
static const int precedence_3 = 3;
static const int precedence_4 = 4;


void shunting_yard(stk <str> &, string);

int precedence (str token);
bool is_left_parenthesis(str); 
bool is_right_parenthesis(str);
bool is_operator(str);
bool is_left_associative(str);
bool is_function (str);