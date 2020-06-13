#ifndef MAIN__H
#define MAIN__H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <string>

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

bool read_pgm(image &);
void generate_matrix_c(double, complejo ***);
int * binary_search(const complejo, complejo ***, int [2], int [2]);
void map_image(image &, image &, complejo (complejo::*function_pointer)(void));


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