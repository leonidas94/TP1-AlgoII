#ifndef _SHUNTING_H_INCLUIDO_
#define _SHUNTING_H_INCLUIDO_

#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include "is_functions.h"
#include "stk.h"
#include "complejo.h"

static const int precedence_2 = 2;
static const int precedence_3 = 3;
static const int precedence_4 = 4;

//ostream & operator << (ostream &, const complejo &);

void shunting_yard(stk <string> &, string[], size_t);

int precedence (string token);

void solve_rpn(stk <string> &, complejo);

#endif