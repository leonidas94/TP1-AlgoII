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
	double get_modulo();
	double get_angulo();

	// Printer
	//ostream& operator<< (ostream& os);
	//const std::string complex_to_string () const;
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
	/*complejo operator ^ (const complejo &); // Potenciacion de complejos
	complejo operator ^ (const double &);*/
	complejo & operator = (const complejo &); // Operador =
	bool operator== (const complejo &);
	bool operator== (const double a);
	bool operator== (const int a);

	// Funciones
	complejo exponencial ();
	complejo conjugar (); // Conjuga el complejo
	complejo inversa ();  // Calcula la inversa
	complejo logaritmo();
	complejo seno();
	complejo pow2();
	complejo complex_pow(const complejo);


	

private:
	double real; // Dos atributos, real e imaginario, se explica solo
	double img;

};

/*ostream & operator << (ostream &out, const complejo &c)
{
    out << c.get_real();
    out << "+i" << c.get_img() << endl;
    return out;
}*/	
ostream & operator << (ostream &, const complejo &);
istream & operator >> (istream &,  complejo &);

#endif