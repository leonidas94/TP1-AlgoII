#ifndef _PARSER_H_INCLUIDO_
#define _PARSER_H_INCLUIDO_

#include <iostream>
#include <string>
#include "is_functions.h"
#include "stk.h"

using namespace std;

string * parse_function(const string, size_t &);

bool parse_math_expression(const string, string *&, size_t &, size_t &);
bool parse_number(const string, string *&, size_t &, size_t &);
bool parse_negative_number(const string, string *&, size_t &, size_t &);
bool parse_negative_j(const string, string *&, size_t &, size_t &);

bool check_operator_at_begining(const string);
bool check_balance (const string );

bool resize_string_array (string *& , size_t &, size_t );
void add_string_to_array(string *& , size_t &, const string &);

#endif