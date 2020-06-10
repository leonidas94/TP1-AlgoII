#include <iostream>
#include "str.h"

bool is_left_parenthesis(str token){        
    return token.compare("(") ||
    	   token.compare("[") ||
    	   token.compare("{") ;      
}  
int main (){

	str new_string;
	str string_igual = "(";
	char * cadena_char = "puto";
	char a = 'a';
	size_t largo;

	cout << a << endl;

	/*string_igual.append(a);

	string_igual.print_str();*/

	cout<<is_left_parenthesis(string_igual)<<endl;




	return 0;
}
