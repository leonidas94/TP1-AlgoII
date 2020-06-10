#include <iostream>
#include "str.h"

int main (){

	str new_string;
	str cadena = "a12";
	char * cadena_char = "puto";
	char a = 'a';
	size_t largo;


	if(cadena.is_number())
		cout << a << endl;

	cadena.print_str();

	return 0;
}
