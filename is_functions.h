#ifndef _IS_FUNCTIONS_H_INCLUIDO_
#define _IS_FUNCTIONS_H_INCLUIDO_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* Modificar este valor si se desean agregar mas funciones en is_functions.cpp*/
#define FUNCTIONS_AMOUNT 8 // Cantidad de funciones matematicas implementadas (exp, ln, re..)

/* En esta libreria se encuentran las funciones utilizadas por el algoritmo de
   parseo y el shunting-yard. En la misma hay funciones simples que reciben char
   o strings y devuelven un booleano dependiendo lo recibido. */

bool is_math_function_initial (const char);
bool is_math_function (string);

bool is_negative_number(const char, const char, size_t);

bool is_operator(char);
bool is_operator(string);

bool is_parenthesis(char);
bool is_left_parenthesis(string); 
bool is_right_parenthesis(string);

bool is_left_associative(string);
bool is_string_digit (string );

#endif