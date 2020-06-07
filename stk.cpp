#include <iostream>
#include "stk.h"



using namespace std;



void stk::stk (){

	array = null; 
	size = 0;
	top = -1; 	//-1 cuando el stack esta vacio
}

void stk::stk (int size){

	array = new string [size];
	this->size = size;
	top = -1;	//-1 cuando el stack esta vacio

}

stk::~stk(){

	delete[] array;
	size = 0;
	top = -1;	//-1 cuando el stack esta vacio

}

string stk::pop(){
	if (top == -1)
	{
		return null;
	}
	return array[top--];
}

void stk::push(const string & str){
	array[++top]= str;
}

bool stk::is_empty(){
	if (top==-1)
	{
		return true;
	}
	return false;
}

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



















