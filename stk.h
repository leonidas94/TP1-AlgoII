#ifndef _STK_H_INCLUIDO_
#define _STK_H_INCLUIDO_

#include <iostream>

using namespace std;


class stk{
	private:

		string * array;
		size_t size;
		int top;


		//lista <char> list;
/*
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
		nodo *ult_;
		size_t tam_;*/


	public:

		stk();
		stk(const array &);
		~stk();

		size_t tamano() const;

		char pop();
		push();
		is_empty();


};

#endif