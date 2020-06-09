#include <iostream>
#include <string>
#include "str.h"

int main (){

	str new_string(6);
	string cadena_juan = "juancho";
	size_t largo;

	largo = new_string.get_len();
	cout << largo << endl;
	
	new_string.set_len(4);
	largo = new_string.get_len();
	cout << largo << endl;


	cout << "string: " << cadena_juan << endl;

	new_string = cadena_juan;

	new_string.print_str();

	largo = new_string.get_len();
	cout << largo << endl;

	return 0;
}