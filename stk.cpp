#include <iostream>
#include "stk.h"



using namespace std;



template<typename T>
stk<T>::nodo::nodo(const T &t) : sig_(0), dato_(t)
{
}

template<typename T>
stk<T>::nodo::~nodo()
{
}

template<typename T>
stk<T>::stk() : pri_(0), tam_(0)
{
}


template<typename T>
stk<T>::~stk()
{
	for (nodo *p = pri_; p; )
	{
		nodo *q = p->sig_;
		delete p;
		p = q;
	}
}

template<typename T>
void stk<T>::pop()
{
	if (tam_ > 0)
	{
		nodo * aux;
		aux = pri_->sig_;
		delete pri_;
		pri_ = aux;
		tam_--;
	}
}


template<typename T>
void stk<T>::push(T t)
{
	nodo *p = new nodo(t);
	p->sig_ = pri_;

	pri_ = p;

	tam_++;
}


// AAGREGAR EXIT SI EL TAMAÑO ES CERO
template<typename T>
T stk<T>::peek()
{
	if (!is_empty())
	{
		return pri_->dato_;
	}
	
}

template<typename T>
bool stk<T>::is_empty()
{
	if (tam_==0)
	{
		return true;
	}
	return false;
}

template <typename T>
stk<T>& stk<T>::operator= (const stk<T>& stk2copy){
	 stk <T> out;
	 nodo * aux;
	 aux = stk2copy.pri_;
	 while (!aux){
	 	out.push(aux.dato_);
	 	aux = aux.sig_;
	 }
}


/***********************LO VIEJO*******************************/
/*void stk::stk (){

	array = null; 
	size = 0;
}

void stk::stk (int size){

	array = new char [size];
	this->size = size;

}

stk::~stk(){

	delete[] array;
	size = 0;

}*/

/*char stk::pop(){


	lista <char> ::iterador it;

	it = list.ultimo();

	char dato = it.dato();

	list.borrar(it.dato());

	return dato;


	char aux [size-1];

	for (int i = 0; i < size-2; ++i)
	{
		aux[i] = array [i];
	}

	char aux_value = array[size-1];

	delete[] array;

	array = new char [this->size-1];

	array = aux;

	return aux_value;
}


void stk::push(char data){

	lista <char> ::iterador it;

	it = lista.ultimo();

	instertar_despues(list,data);
 	
}*/



















