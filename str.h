#ifndef _STR_H_INCLUIDO_
#define _STR_H_INCLUIDO_

#include <iostream>

using namespace std;

class str{

public:

	// Constructores y destructor
	str(); // Constructor por defecto
	str(const char *);
	str(const size_t ); // Constructor por longitud de la cadena
	str(const str &); // Constructor por copia, copia una string en otra
	~str(); // Destructor, no tiene que destruir nada porque no pedimos memoria

	// Setters y Getters
	void set_len(const size_t);
	size_t get_len();

	// Printer
	void print_str();

	// Operadores

	str operator=(const str & );
	str operator=(char *);
	char operator[]( size_t );

	// Funciones
	void append(const str &);
	bool compare(const str &);



private:
	char * my_str; 
	size_t len;
};

#endif