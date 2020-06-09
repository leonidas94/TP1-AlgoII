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

/*
template<typename T>
stk<T>::stk(const stk &orig) : pri_(0), ult_(0), tam_(orig.tam_)
{
	nodo *iter;
	nodo *ant;

	// Recorremos la secuencia original en sentido directo. En cada paso,
	// creamos un nodo, copiando el dato correspondiente, y lo enganchamos
	// al final de nuestra nueva lista.
	//
	for (iter = orig.pri_, ant = 0; iter != 0; iter = iter->sig_)
	{
		// Creamos un nodo, copiando el dato, y lo enganchamos en e
		// final de nuestra lista.
		//
		nodo *nuevo = new nodo(iter->dato_);
		nuevo->ant_ = ant;
		nuevo->sig_ = 0;

		// Si ésta no es la primera pasada, es decir, si no se trata
		// del primer nodo de la lista, ajustamos el enlace sig_ del
		// nodo anterior.
		//
		if (ant != 0)
			ant->sig_ = nuevo;

		// Además, tenemos que ajustar los punteros a los elementos
		// distinguidos de la secuencia, primero y último. En el caso
		// de pri_ (enlace al primer elemento), esto lo vamos a
		// hacer una única vez; para el caso de ult_, iremos tomando
		// registro del último nodo procesado, para ajustarlo antes
		// de retornar.
		//
		if (pri_ == 0)
			pri_ = nuevo;
		
	}
	
	// Ajustamos el puntero al último elemento de la copia.
	ult_ = ant;
}*/

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
	return pri_->dato_;
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



















