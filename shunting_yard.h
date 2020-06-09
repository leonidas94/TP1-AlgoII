#include <iostream>
#include "stk.h"


static const int precedence_2 = 2;
static const int precedence_3 = 3;
static const int precedence_4 = 4;



bool is_left_parenthesis(char token); 
bool is_right_parenthesis(char token);
bool is_operator(char);
int precedence (char token);
bool is_left_associative(char);
void shunting_yard(stk <char> &, string);