#include <iostream>
#include <string>
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

str str::operator= (const string & string_a_igualar){

	//if(strlen(string_a_igualar!=0){	}

	if(len!=string_a_igualar.length()){
		len=string_a_igualar.length();
		delete[] my_str;
		my_str = new char[len];
	}

	for (size_t i = 0; i < len; ++i){
		my_str[i]=string_a_igualar[i];	
	}	

	return *this;
}


str str::operator+ (const str & str_to_append){

	str aux=*this;

	len+=str_to_append.len;
	delete[] my_str;
	my_str = new char[len];

	for (size_t i = 0; i < aux.len; ++i){
		my_str[i]=aux[i];	
	}

	for (size_t i = aux.len; i < len; ++i){
		my_str[i]=str_to_append[i];	
	}	

	return *this;
}

str str::operator+ (const string & ){

}