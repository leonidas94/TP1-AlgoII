#include <iostream>
#include "complejo.h"
//#include <cmath>
#include <string>
#include <sstream>

using namespace std;

// Constructor por defecto
complejo::complejo(){ 
	real = 0;
	img = 0;
}

// Constructor normal, primer argumento es real, segundo es img.
complejo::complejo(const double arg_real, const double arg_img){
	real = arg_real;
	img = arg_img;
}

// Constructor por copia, simplemente copia los dos valores de un complejo a otro
complejo::complejo(const complejo & arg_complejo){
	real = arg_complejo.real;
	img = arg_complejo.img;
}

// Destructor
complejo::~complejo(){}

// Setters
void complejo::set_real(const double arg_real){ // Setea la parte real
	real = arg_real;	
}

void complejo::set_img(const double arg_img){ // Setea la parte imaginaria
	img = arg_img;
}

// Getters
double complejo::get_real(void) const{	// Obtiene la parte real
	return real;
}

double complejo::get_img(void) const{	// Obtiene la parte imaginaria
	return img;
}

double complejo::get_modulo(){ // Obtiene le módulo
	return sqrt((this->real)*(this->real) + (this->img)*(this->img));
}

double complejo::get_angulo(){	// Obtiene el angulo
	return atan((this->img)/(this->real));
}

// Printer
/*
ostream& complejo::operator<< (ostream& os){
	return os << real << "+ j*" << img;
}*/
/*
string complejo::complex_to_string (){
	string aux = "";

	ostringstream ss;
  	ss << real;
	aux.append(ss.str());
	aux.append("+j*");
	ostringstream ss1;
	ss1 << img;
	aux.append(ss1.str());


	return aux;
}*/
/*
const std::string complejo::complex_to_string()const
{
    return (std::to_string(real)+"+"+std::to_string(imaginary)+"i");
//    std::cin.ignore(50, '\n');
//    std::cin.get();
    }*/

string complejo::to_string(){

  	ostringstream x_convert;
	x_convert << *this;
	return x_convert.str();
}


bool complejo::operator== (const complejo& a){
 	
	if (real == a.real && img == a.img)
		return true;
	return false;
}

bool complejo::operator== (const double a){
 	
	if (real == a && img == 0)
		return true;
	return false;
}

bool complejo::operator== (const int a){
 	
	if (real == a && img == 0)
		return true;
	return false;
}

// Operador SUMA con un complejo
complejo complejo::operator + (const complejo & complejo_a_sumar){
	complejo aux;
	aux.real = (this->real) + complejo_a_sumar.real;
	aux.img = (this->img) + complejo_a_sumar.img;
	return aux;
}

// Operador SUMA con un escalar
complejo complejo::operator + (const double & double_a_sumar){
	complejo aux;
	aux.real = (this->real) + double_a_sumar;
	aux.img = (this->img);
	return aux;
}

// Operador RESTA con un complejo
complejo complejo::operator - (const complejo & complejo_a_restar){
	complejo aux;
	aux.real = (this->real) - complejo_a_restar.real;
	aux.img = (this->img) - complejo_a_restar.img;
	return aux;
}

// Operador RESTA con un escalar
complejo complejo::operator - (const double & double_a_restar){
	complejo aux;
	aux.real = (this->real) - double_a_restar;
	aux.img = (this->img);
	return aux;
}

// Operador MULTIPLICACION por un complejo
complejo complejo::operator * (const complejo & A){
	complejo aux;
	aux.real = (this->real * A.real) - (this->img * A.img);
	aux.img = (this->real * A.img) + (this->img * A.real);
	return aux;
}

// Operador MULTIPLICACION por un escalar
complejo complejo::operator * (const double & A){
	complejo aux;
	aux.real = (this->real * A);
	aux.img = (this->img * A);
	return aux;
}

// Operador DIVISION por un complejo
complejo complejo::operator / (const complejo & divisor){
	complejo aux;
	double a = this->real;
	double b = this->img;
	double c = divisor.real;
	double d = divisor.img;

	aux.real = (a*c)/(c*c + d*d) + (b*d)/(c*c + d*d);
	aux.img = (b*c)/(c*c + d*d) - (a*d)/(c*c + d*d);
	return aux;
}

// Operador DIVISION por un escalar
complejo complejo::operator / (const double & divisor){
	complejo aux;
	aux.real = this->real / divisor;
	aux.img = this->img / divisor;
	return aux;
}

// Operador IGUAL
complejo & complejo::operator = (const complejo & complejo_a_igualar){
	real=complejo_a_igualar.real;
	img=complejo_a_igualar.img;
	return *this;
}
/*
complejo complejo:: operator^ (const complejo){

}

complejo complejo:: operator^ (const double exponente){
	
}
*/
 // Funciones

// EXPONENCIAL
complejo complejo::exponencial(){

  complejo aux;

  double modulo = exp(this->real);
  double angulo = this->img;

  aux.real = modulo*cos(angulo);
  aux.img = modulo*sin(angulo);

  return aux;
}

// CONJUGAR
complejo complejo::conjugar (){
	complejo aux;
	aux.real = this->real;
	aux.img = -(this->img);
	return aux;
}

// INVERSA
complejo complejo::inversa (){
	complejo aux;
	aux=this->conjugar();
	aux.real=aux.real/(aux.get_modulo());
	aux.img=aux.img/(aux.get_modulo());
	return aux;
}

// LOGARITMO
complejo complejo::logaritmo(){

  complejo aux;

  double modulo = this->get_modulo();

  aux.real = log(modulo);
  aux.img = atan2(this->img,this->real);

  return aux;
}

// SENO
complejo complejo::seno(){

  complejo aux;

  aux.real = sin(real)*cosh(img);
  aux.img = cos(real)*sinh(img);

  return aux;
}

// CUADRADO

complejo complejo::pow2(){

	complejo aux;

  	aux.real = real*real-img*img;
  	aux.img = real*img*2;

 	return aux;
}

complejo complejo::complex_pow(const complejo a){

	double r = this->get_modulo();
	double th = this->get_angulo();
	//cout<<"modulp: "<<r<<"fase: "<<th<<endl;

	r = pow(r,a.real)*exp(-th*a.img);
	cout<<"en el medios"<<th<<endl;
	double th2 = (log(r)*a.img) + (th*a.real);

	cout<<th2<<endl;
	cout<<a.real<<endl;
	cout<<"log: "<<th2*a.real<<endl;
	//cout<<"modulp: "<<r<<"fase: "<<th<<endl;
  	return complejo(r*cos(th2),r*sin(th2));
}


ostream & operator << (ostream &out, const complejo &c)
{
    out << c.get_real();
    out << " " << c.get_img() << "j" << endl;
    return out;
}	


istream & operator >> (istream &in,  complejo &c)
{	
	double aux;
    in >> aux;
    c.set_real(aux);
    in >> aux;

    if (!in.eof())
    {
    	c.set_img(aux);
    }
    
    return in;
}