#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <math.h>

#include "image.h"
#include "complejo.h"
#include "main_prueba_validaciones.h"
#include "stk.h"
#include "str.h"

using namespace std; 

//*****************************VARIABLES GLOBALES*****************************//

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static string PGM_IDENTIFIER = "P2";

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static string entered_function;		// Funcion leida directamente de consola

static char functions_initials[]= {'l', 'r', 'i', 'e', 'a', 'p'};
static string math_functions[]= {"exp", "ln", "re", "im", "abs", "phase" };

// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){
	string * string_array;

	cmdline cmdl(options);	       // Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv);        // Metodo de parseo de la clase cmdline

	cout << entered_function << endl;

	string_array = parse_function(entered_function);

	cout << string_array[3] << endl;

	return 0;
}

string * parse_function(const string function){		// Valido y parseo la funcion ingresada
	size_t i = 0, string_array_size= 0;
	string * string_array;		// aca devuelvo el string array con la funcion parseada
								// si es que fue ingresada correctamente

	if (!is_balanced(function)){	
		cout << "No esta balanceada" << endl;
		exit(0);
	}

	while (i < function.length()){

		if (function[i] == ' ')
			i++;
		if (is_math_function_initial(function[i]) && function[i+1]!='-' && !isdigit(function[i+1])){
			if (!parse_math_expression(function, string_array, string_array_size, i)){
				cout << "error, funcion matematica erronea" << endl;
				exit(0);
			}
			i++;
		}
		i++;

	}

	return string_array;
}


bool is_math_function_initial (const char letter){ // Comparo contra las iniciales de las funciones
	size_t size = sizeof(functions_initials) / sizeof(functions_initials[0]);

	for (size_t i=0 ; i< size ; i++){
		if (letter == functions_initials[i]){
			return true;
		}
	}
	return false;
}


// Comprueba la funcion y la guarda en string array
bool parse_math_expression (const string function, string *& string_array, size_t & string_array_size, size_t & position){	
	string aux_string = "";

cout << "encontro funcion en pos: " << position << endl;

	while (function[position] != '('){
		if (position >= function.length()){
			cout << "ERROR no encontro parentesis ( parseando"<< endl;
			exit (0);
		}
		aux_string.append(1, function[position]);
		position++;
	}

	for (size_t i = 0; i< FUNCTIONS_AMOUNT; i++){
		if (aux_string == math_functions[i]){
			add_string_to_array(string_array, string_array_size, aux_string);
			return true;
		}
	}
	return false;

}


void add_string_to_array(string *& string_array, size_t & string_array_size, const string & str2add){

	resize_string_array(string_array, string_array_size, 1);

	string_array[string_array_size-1] = str2add;

}


bool resize_string_array (string *& string_array, size_t & string_array_size, size_t i){	// pido memoria para string array de tamaño i
	string * aux_string_array;

	if (string_array_size == 0){	// Primer caso
		string_array = new string [i];
		string_array[0]="";
		string_array_size += i;
		return true;
	}

	if (string_array_size>0){	// Luego del primer caso

		aux_string_array = new string [string_array_size]; // pido memoria para el string array aux

		for (size_t j = 0; j< string_array_size; j++){ // copio el string array a un auxiliar
			aux_string_array[j] = string_array [j];
		}

		delete[] string_array;
		string_array = new string [string_array_size+i];	// Pido memoria para i lugar mas

		for (size_t j = 0; j< string_array_size ; j++){ // recupero la informacion que tenia antes
			string_array[j] = aux_string_array [j];
		}

		for (size_t j = string_array_size; j < string_array_size+i; j++){	//Seteo las nuevas posiciones en vacio
			string_array[j] = "";
		}
		string_array_size += i;
		delete[] aux_string_array;

		return true;
	}

	return true;
}

bool is_balanced (const string function){
	stk <char> stack;
	bool balanced = true;

	for (size_t i = 0; i < function.length() && balanced == true; ++i)
	{
		switch(function[i]){
			case '{':
			case '[':
			case '(':
				stack.push(function[i]);
				break;
			case '}':
				if (!stack.is_empty() && stack.peek() == '{')
					stack.pop();
				else
					balanced = false;
				break;
			case ']':
				if (!stack.is_empty() && stack.peek() == '[')
					stack.pop();
				else
					balanced = false;
				break;	
			case ')':
				if (!stack.is_empty() && stack.peek() == '(')
					stack.pop();
				else
					balanced = false;
				break;				
		}
	}
	if (!stack.is_empty())
		balanced = false;
	return balanced;
}



//************************FUNCIONES DE CMDLINE************************//

static void opt_input(string const &arg){

	if (arg == "-") {
		iss = &cin;		// Se establece la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}
	// Verificamos que el stream este OK.
	if (!iss->good()) {
		cerr << "No se puede abrir el archivo de entrada: "<< arg<< "."<< endl;
		exit(1);
	}
}

static void opt_output(string const &arg){

	if (arg == "-") {	// Si el input es -,
		oss = &cout;	// se establece la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}
	if (!oss->good()) {
		cerr << "No se puede abrir el archivo de salida: "<< arg<< "."<< endl;
		exit(1);
	}
}

static void opt_function(string const &arg){
	entered_function = arg;
}

static void opt_help(string const &arg){  // La opción -h imprime el formato de ejecución
  cout << "cmdline -f function [-i file] [-o file]" << endl;
  cout << "funciones: z, expz, conjugar, inversa, log, sin, pow" << endl;
	exit(0);
}

//***********************METODOS DE CMDLINE***********************//

cmdline::cmdline(){}

cmdline::cmdline(option_t *table) : option_table(table){}

void cmdline::parse(int argc, char * const argv[]) {
#define END_OF_OPTIONS(p)       \
	((p)->short_name == 0   \
	 && (p)->long_name == 0 \
	 && (p)->parse == 0)

	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op)
		op->flags &= ~OPT_SEEN;

	for (int i = 1; i < argc; ++i) {

		if (argv[i][0] != '-') {
			cerr << "Argumento inválido." << argv[i] << endl;
			exit(1);
		}

		if (argv[i][1] == '-'
		    && argv[i][2] == 0)
			break;

		if (argv[i][1] == '-')
			i += do_long_opt(&argv[i][2], argv[i + 1]);
		else
			i += do_short_opt(&argv[i][1], argv[i + 1]);
	}

	for (option_t *op = option_table; !END_OF_OPTIONS(op); ++op) {
#define OPTION_NAME(op) \
	(op->short_name ? op->short_name : op->long_name)
		if (op->flags & OPT_SEEN)
			continue;
		if (op->flags & OPT_MANDATORY) {
			cerr << "Opción "<< "-"<< OPTION_NAME(op)<< " es obligatoria."<< "\n";
			exit(1);
		}
		if (op->def_value == 0)
			continue;
		op->parse(string(op->def_value));
	}
}

int cmdline::do_long_opt(const char *opt, const char *arg) {
	// Se recorre la tabla de opciones, y se busca la entrada larga que se corresponda 
  // con la opción de línea de comandos. De no encontrarse, se indica el error correspondiente.
	
	for (option_t *op = option_table; op->long_name != 0; ++op) {
		if (string(opt) == string(op->long_name)) {
			// Se marca esta opción como usada en forma explícita, para evitar tener que inicializarla con el valor por defecto.

			op->flags |= OPT_SEEN;

			if (op->has_arg) {
				if (arg == 0) { // Verificamos que se provea un argumento
					cerr << "La opción requiere el argumento: "<< "--"<< opt<< "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				op->parse(string("")); // Opción sin argumento.
				return 0;
			}
		}
	}
	// Error: opción no reconocida.
	cerr << "Opción desconocida: "<< "--"<< opt<< "."<< endl;
	exit(1);
	return -1;
}

int cmdline::do_short_opt(const char *opt, const char *arg) {
	option_t *op;

	for (op = option_table; op->short_name != 0; ++op) {

		if (string(opt) == string(op->short_name)) {
			op->flags |= OPT_SEEN;
			if (op->has_arg) {
				if (arg == 0) {	
					cerr << "La opción requiere el argumento: "<< "-"<< opt<< "\n";
					exit(1);
				}
				op->parse(string(arg));
				return 1;
			} else {
				op->parse(string(""));
				return 0;
			}
		}
	}
	cerr << "Opción desconocida: "<< "-"<< opt << "." << endl;
	exit(1);
	return -1;
}


// *******************************FUNCIONES**********************************//


// Esta funcion lee del archivo de input y llena la imagen VACIA que se le pasa como argumento. 
