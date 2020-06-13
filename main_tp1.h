#ifndef MAIN__H
#define MAIN__H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <string>
#include "shunting_yard_v2.h"

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

#define FUNCTION_Z "z"
#define FUNCTION_EXPZ "expz"
#define FUNCTION_CONJUGAR "conjugar"
#define FUNCTION_INVERSA "inversa"
#define FUNCTION_LOGARITMO "log"
#define FUNCTION_SENO "sin"
#define FUNCTION_POW "pow"
#define NUL '\0'

#define FUNCTIONS_AMOUNT 6 // Cantidad de funciones matematicas implementadas (exp, ln, re..)

struct option_t {
	int has_arg;
	const char *short_name;
	const char *long_name;
	const char *def_value;
	void (*parse)(std::string const &); // Puntero a función de opciones
	int flags;
};

//************************DECLARACION FUNCIONES************************//

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);

string * parse_function(const string, size_t &);

bool is_balanced (const string );
bool is_math_function_initial (const char);

bool parse_math_expression(const string, string *&, size_t &, size_t &);
bool parse_number(const string, string *&, size_t &, size_t &);// agregue eso
bool parse_negative_number(const string, string *&, size_t &, size_t &);
bool resize_string_array (string *& , size_t &, size_t );

void add_string_to_array(string *& , size_t &, const string &);



/********************************/

bool is_operator(char);
bool is_parenthesis(char);

class cmdline {
	// Este atributo apunta a la tabla que describe todas las opciones a procesar. 
	// Por el momento, sólo puede ser modificado mediante contructor, y debe finalizar con un elemento nulo.

	option_t *option_table;

	// El constructor por defecto cmdline::cmdline(), es privado, para evitar construir "parsers" 
	// (analizador sintáctico, recibe una palabra y lo interpreta en una acción dependiendo su 
	// significado para el programa sin opciones. Es decir, objetos de esta clase sin opciones.

	cmdline();
	int do_long_opt(const char *, const char *);
	int do_short_opt(const char *, const char *);
public:
	cmdline(option_t *);
	void parse(int, char * const []);
};

#endif