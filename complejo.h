#ifndef _COMPLEJO_H_INCLUIDO_
#define _COMPLEJO_H_INCLUIDO_

#include <iostream>

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
	double get_modulo();
	double get_angulo();

	// Printer
	void print_complejo();

	// Operadores
	complejo operator + (const complejo &); // Suma de complejos
	complejo operator + (const double &);
	complejo operator - (const complejo &); // Resta de complejos
	complejo operator - (const double &);
	complejo operator * (const complejo &); // Multiplicacion de complejos
	complejo operator * (const double &);
	complejo operator / (const complejo &); // Division de complejos
	complejo operator / (const double &);
	complejo & operator = (const complejo &); // Operador =

	// Funciones
	complejo exponencial ();
	complejo conjugar (); // Conjuga el complejo
	complejo inversa ();  // Calcula la inversa
	complejo logaritmo();
	complejo seno();
	complejo pow2();


private:
	double real; // Dos atributos, real e imaginario, se explica solo
	double img;

};

#endif