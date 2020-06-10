#include <iostream>
#include "str.h"

using namespace std;

// Constructor por defecto
str::str(){
	my_str=NULL; 
	len=0;
}

// Constructor por longitud
str::str(const size_t a){
	my_str = new char[a];
	len=a;
}

// Constructor por copia
str::str(const char * str_arg){

	size_t length = 0;

	while(str_arg[length]!='\0'){length++;}

	my_str = new char[length];
	len = length;

	for (size_t i = 0; i < len; ++i){
		my_str[i]=str_arg[i];	
	}
}

// Constructor por copia
str::str(const str & str_arg){
	my_str = new char[str_arg.len];
	len = str_arg.len;

	for (size_t i = 0; i < str_arg.len; ++i){
		my_str[i]=str_arg.my_str[i];	
	}
}

// Destructor
str::~str(){

	if(my_str){
		delete[] my_str;
		len=0;	
	}
}

void str::print_str(){

	if(len>0){
		cout << my_str << endl;
	}
}


	// Setters y Getters
void str::set_len(const size_t a){
	len=a;
}

size_t str::get_len(){
	return len;
}



str str::operator= (const str & string_a_igualar){

	my_str=string_a_igualar.my_str;
	len=string_a_igualar.len;

	return *this;
}


str str::operator= (char * string_a_igualar){

	size_t length=0;

	while(string_a_igualar[length]!='\0'){
		length++;
	}

	if(len!=length){
		len=length;
		delete[] my_str;
		my_str = new char[len];
	}

	for (size_t i = 0; i < len; ++i){
		my_str[i]=string_a_igualar[i];	
	}	

	return *this;
}


char str::operator[]( size_t i){
	if(i < len && i >= 0)
		return my_str[i];
	
	else{
		cout << "Array index out of bounds." << endl; 
   }
   return 0; // NO SABEMOS QUE DEVOLVER
}


void str::append (const str & str_to_append){

	str aux=*this;

	len+=str_to_append.len;

	delete[] my_str;
	my_str = new char[len];

	for (size_t i = 0; i < aux.len; ++i){
		my_str[i]=aux.my_str[i];
	}

	for (size_t i = aux.len; i < len; ++i){
		my_str[i]=str_to_append.my_str[i-aux.len];
	}	
}



void str::append (const char & char_to_append){

	str aux=*this;

	len++;

	delete[] my_str;
	my_str = new char[len];

	for (size_t i = 0; i < aux.len; ++i){
		my_str[i]=aux.my_str[i];
	}

		my_str[aux.len]=char_to_append;
}



bool str::compare(const str & str2comp){

	if(len != str2comp.len){return false;}

	for (size_t i = 0; i < len; i++){
		if(my_str[i] != str2comp.my_str[i])
		return false;	
	}

	return true;	
}

bool str::is_number(){

	if(str=0 || str=1 || str=2 || str=3 || str=4 || str=5 || str=6 || str=7 || str=8 || str=9 || )
		return true;
	return false;
}