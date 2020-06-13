#ifndef _STK_H_INCLUIDO_
#define _STK_H_INCLUIDO_

#include <iostream>

using namespace std;

template<typename T>
class stk{
	private:

/*		string * array;
		size_t size;
		int top;
*/

		//lista <char> list;

		class nodo
		{

		friend class stk;

		nodo *sig_;
		T dato_;

		//bool flag_sign;

		public:
		nodo(T const&);
		~nodo();
		};

		nodo *pri_;
		size_t tam_;


	public:

		stk();
		stk (const stk<T>&);
		~stk();

		size_t stk_size() const;

		void pop();
		void push(T);
		T peek();
		bool is_empty();
		stk<T>& operator= (const stk<T>&);



};


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

template <typename T>
stk<T>::stk (const stk<T>& stk2copy){

	nodo * aux;
	nodo * aux2;
	if (stk2copy.tam_>0)
	{
		pri_ = new nodo((stk2copy.pri_)->dato_);
		aux = (stk2copy.pri_)->sig_;
		aux2 = pri_;

		while (aux){
			aux2->sig_ = new nodo(aux->dato_);
			aux = aux->sig_;
			aux2 = aux2->sig_;

		}
		tam_=stk2copy.tam_;
	}
	else{
		this->pri_=0;
		this->tam_=0;
	}
}

template <typename T>
stk<T>& stk<T>::operator= (const stk<T>& stk2copy){

	for (nodo *p = pri_; p; )
	{
		nodo *q = p->sig_;
		delete p;
		p = q;
	}

	nodo * aux;
	nodo * aux2;
	if (stk2copy.tam_>0)
	{
		pri_ = new nodo((stk2copy.pri_)->dato_);
		aux = (stk2copy.pri_)->sig_;
		aux2 = pri_;

		while (aux){
			aux2->sig_ = new nodo(aux->dato_);
			aux = aux->sig_;
			aux2 = aux2->sig_;

		}
		tam_=stk2copy.tam_;
	}
	else{
		this->pri_=0;
		this->tam_=0;
	}
	return *this;
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
	if (pri_)
	{
		nodo * aux;
		aux = pri_->sig_;
		delete pri_;
		pri_ = aux;
		tam_--;
	}else 
		return;

}


template<typename T>
void stk<T>::push(T t)
{
	nodo *p = new nodo(t);
	p->sig_ = pri_;

	pri_ = p;

	tam_++;
}



template<typename T>
T stk<T>::peek()
{
	if (!is_empty())
		return pri_->dato_;

}

template<typename T>
bool stk<T>::is_empty()
{
	if (!pri_)
	{
		return true;
	}
	return false;
}

template<typename T>
size_t stk<T>::stk_size() const{
	return tam_;
}






#endif