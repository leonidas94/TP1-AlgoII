#ifndef _COMPLEJO_H_INCLUIDO_
#define _COMPLEJO_H_INCLUIDO_

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class complejo{

public:

	// Constructores y destructor
	complejo(); // Constructor por defecto
	complejo(const double , const double ); // Constructor normal, usa doubles
	complejo(const complejo &); // Constructor por copia, simplemente copia los dos valores de un complejo a otro
	~complejo(); // Destructor, no tiene que destruir nada porque no pedimos memoria

	// Setters y Getters
	void set_real(const double);
	void set_img(const double);
	double get_real() const;
	double get_img()const;
	double get_abs()const;
	double get_phase()const;

	// Printer
	string to_string();

	// Operadores
	complejo operator + (const complejo &); // Suma de complejos
	complejo operator + (const double &);
	complejo operator - (const complejo &); // Resta de complejos
	complejo operator - (const double &);
	complejo operator * (const complejo &); // Multiplicacion de complejos
	complejo operator * (const double &);
	complejo operator / (const complejo &); // Division de complejos
	complejo operator / (const double &);
	

	complejo & operator = (const complejo &); 
	complejo operator = (const double);
	bool operator== (const complejo &);		 
	bool operator== (const double a);
	bool operator== (const int a);

	// Funciones
	complejo exponencial ();// Calcula la exponencial
	complejo conjugar (); 	// Conjuga el complejo
	complejo inversa ();  	// Calcula la inversa
	complejo logaritmo();	// Calcula el logaritmo
	complejo seno();		// Calcula el seno
	complejo complex_pow(const complejo);	// Eleva un complejo a otro
	complejo complex_pow(const double);		// Eleva un complejo a un double
	complejo re ();							// Devuelve la parte real
	complejo im ();							// Devuelve la parte imaginaria como imaginario puro

private:
	double real; // Dos atributos, real e imaginario
	double img;

};

ostream & operator << (ostream &, const complejo &); // Imprimie complejo en ostream
istream & operator >> (istream &,  complejo &);		 // Lee complejo desde istream

#endif