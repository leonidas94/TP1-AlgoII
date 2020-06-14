#ifndef _IMAGE_H_INCLUIDO_
#define _IMAGE_H_INCLUIDO_

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#define FUNCTIONS_AMOUNT 6 // Cantidad de funciones matematicas implementadas (exp, ln, re..)

string * parse_function(const string, size_t &);

bool parse_math_expression(const string, string *&, size_t &, size_t &);
bool parse_number(const string, string *&, size_t &, size_t &);
bool parse_negative_number(const string, string *&, size_t &, size_t &);

bool check_operator_at_begining(const string);
bool is_balanced (const string );
bool is_math_function_initial (const char);
bool is_operator(char);
bool is_parenthesis(char);

bool resize_string_array (string *& , size_t &, size_t );
void add_string_to_array(string *& , size_t &, const string &);

#endif