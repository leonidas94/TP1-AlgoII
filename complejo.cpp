#include "complejo.h"

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

double complejo::get_abs() const{ // Obtiene le módulo
	return sqrt(((this->real)*(this->real)) + ((this->img)*(this->img)));
}

double complejo::get_phase() const{	// Obtiene el angulo
	return atan2((this->img),(this->real));
}

// Combierte un complejo a una string con el formato "real imaginario j"
string complejo::to_string(){

  	ostringstream x_convert;
	x_convert << *this;
	return x_convert.str();
}

// Compara dos numeros complejos
bool complejo::operator== (const complejo& a){
 	
	if (real == a.real && img == a.img)
		return true;
	return false;
}

// Compara un complejo con un double
bool complejo::operator== (const double a){
 	
	if (real == a && img == 0)
		return true;
	return false;
}

// Compara un complejo con un int
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

complejo complejo::operator = (const double num_a_igualar){

	return complejo (num_a_igualar,0);
}

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
	aux.real=aux.real/(aux.get_abs());
	aux.img=aux.img/(aux.get_abs());
	return aux;
}

// LOGARITMO
complejo complejo::logaritmo(){

  complejo aux;

  double modulo = this->get_abs();

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


// Complejo elevado a complejo
complejo complejo::complex_pow(const complejo a){

	double r = this->get_abs();
	double th = this->get_phase();

	double r2 = pow(r,a.real)*exp(-th*a.img);

	double th2 = (log(r)*a.img) + (th*a.real);

  	return complejo(r2*cos(th2),r2*sin(th2));
}

// Complejo elevado a un numero
complejo complejo::complex_pow(const double a){

	double r = this->get_abs();
	double th = this->get_phase();

	double r2 = pow(r,a);
	double th2 = (th*a);

  	return complejo(r2*cos(th2),r2*sin(th2));
}

// Devuelve la parte real como un complejo real puro
complejo complejo::re(){
	return complejo (real,0);
}

// Devuelve la parte imaginaria de un complejo como un imaginario puro
complejo complejo::im(){
	return complejo (0,img);
}

// Imprime el numero complejo en un ostream
ostream & operator << (ostream &out, const complejo &c){
    out << c.get_real();
    out << " " << c.get_img() << " j";
    return out;
}	

// Lee un numero complejo con formato "real imaginario j"
istream & operator >> (istream &in,  complejo &c){	
	double aux;
	string temp;

    in >> temp;

    stringstream(temp) >> aux;
    c.set_real(aux);

    in >> temp;

    if (!in.eof()){
    	stringstream(temp) >> aux;
    	c.set_img(aux);
    }    
    return in;
}