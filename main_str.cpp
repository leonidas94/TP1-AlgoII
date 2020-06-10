#include <iostream>
#include "str.h"

int main (){

	str new_string;
	str string_igual = "juancho";
	char * cadena_char = "puto";
	char a = 'a';
	size_t largo;

	cout << a << endl;

	string_igual.append(a);

	string_igual.print_str();

	return 0;
}
