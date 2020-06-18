#ifndef _STK_H_INCLUIDO_
#define _STK_H_INCLUIDO_

#include <iostream>

using namespace std;

template<typename T>
class stk{
	private:

		class nodo
		{

		friend class stk;

		nodo *sig_;
		T dato_;

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
		bool peek(T &);
		bool is_empty();
		stk<T>& operator= (const stk<T>&);



};

// Constructor de nodo
template<typename T>
stk<T>::nodo::nodo(const T &t) : sig_(0), dato_(t)
{
}

// Destructor de nodo
template<typename T>
stk<T>::nodo::~nodo()
{
}

// Constructor por defecto del stk
template<typename T>
stk<T>::stk() : pri_(0), tam_(0)
{
}

// Constructor por copia del stk
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

// Destructor
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

// Operador= : se la asigna a un stack el contenido del otro. Se 
// crean dinamicamente los nuevos nodos
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

// Funciones

// Pop: Desapila el ultimo elemento del stack, reasigna el puntero 
// para no perder a los demas elementos y libera la memoria correspondiente
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

// Push: Apila un elemento en el stack, creando un nuevo nodo y
// reasignando los punteros
template<typename T>
void stk<T>::push(T t)
{
	nodo *p = new nodo(t);
	p->sig_ = pri_;

	pri_ = p;

	tam_++;
}


// Peek: Toma el ultimo elemento en el stack sin desapilarlo,
// en caso de que el stack este vacio devuelve false si no
// retorna true
template<typename T>
bool stk<T>::peek(T & t)
{
	if (!is_empty()){
		t = pri_->dato_;
		return true;
	}
	return false;
}

// Is_empty: Corrobora el estado del stack, si se encuentra o
// no vacio
template<typename T>
bool stk<T>::is_empty()
{
	if (!pri_)
	{
		return true;
	}
	return false;
}

// Stk_size: Devuelve el tamaño del stack
template<typename T>
size_t stk<T>::stk_size() const{
	return tam_;
}

#endif