#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <string>
#include <vector>

#include "image.h"
#include "complejo.h"
#include "main_prueba_shunting_v2.h"
#include "stk.h"
#include "shunting_yard_v2.h"
#include "str.h"

using namespace std; 

//*****************************VARIABLES GLOBALES*****************************//

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static string entered_function;

// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){
  	string output_queue = "";

	cmdline cmdl(options);	       // Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv);        // Metodo de parseo de la clase cmdline

	cout<<entered_function<<endl;
  	/*shunting_yard(output_queue);   // 
  	cout<<"final: "<<output_queue<<endl;*/


  	/*stringstream ss (entered_function);
 	while(!ss.eof()){
  	ss>>temp;
  	if(stringstream(temp) >> auxd)
  		cout <<"imprimo el numero: "<<auxd<<endl;
  	else
		cout <<"imprimo el simbolo: "<<temp<<endl;
	}*/

	stk <str> output;			//Stack de clase str
	shunting_yard(output,entered_function);
	while(!output.is_empty()){
		cout<<"Out:"<<output.peek()<<endl;
		output.pop();
	}
/*
  	stringstream(temp) >> auxd;
  	cout <<"imprimo el temp: "<<auxd<<endl;
  	ss>>temp;
  	cout <<"imprimo el: "<<temp<<endl;
  	ss>>temp;
  	if(stringstream(temp) >> auxd)
  		cout <<"imprimo el temp: "<<auxd<<endl;
  	else
		cout <<"imprimo el: "<<temp<<endl;*/

	/*if (is_blanaced(entered_function))
		cout<<"Está blanceada"<<endl;
	else
		cout<<"No está balanceada"<<endl;*/

	return 0;
}

bool is_blanaced (const string function){
	stk <char> stack;
	bool balanced = true;

	for (int i = 0; i < function.length() && balanced == true; ++i)
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