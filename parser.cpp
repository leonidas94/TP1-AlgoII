#include <iostream>
#include <string>
#include "parser.h"
#include "stk.h"

using namespace std;

static char functions_initials[]= {'l', 'r', 'i', 'e', 'a', 'p'};
static string math_functions[]= {"exp", "ln", "re", "im", "abs", "phase" };

string * parse_function(const string function, size_t & string_array_size){		// Valido y parseo la funcion ingresada
	size_t i = 0;
	string * string_array;		// Aca devuelvo el string array con la funcion parseada
								// si es que fue ingresada correctamente

	if (!is_balanced(function)){	
		cout << "No esta balanceada" << endl;
		exit(0);
	}
	if (!check_operator_at_begining(function)){	
		cout << "Error, no puede comenzar con " << function[0] << endl;
		exit(0);
	}
	//CLEAN SPACES

	while (i < function.length()){	// Recorro char por char

		// Guardo expresiones matematicas (exp, ln, phase,...)
		if (  is_math_function_initial(function[i]) &&	// Si es la inicial de una funcion mat Y
			  function[i+1]!='-' &&						// si el siguiente no es un guion Y
			  !isdigit(function[i+1])  ){				// si el siguiente no es un digito

			if (!parse_math_expression(function, string_array, string_array_size, i)){	// Trato de parsear
				cout << "error, funcion matematica erronea" << endl;					// la f. mat.
				exit(0);
			}
		}

		// Guardo numeros o numeros que empiecen con punto
		else if (  isdigit(function[i]) ||							// Si es un digito O
				   (function[i]=='.' && isdigit(function[i+1]))  ){ // es un punto Y el siguiente un digito

			if (!parse_number(function, string_array, string_array_size, i)){ // Trato de parsear el numero
				cout << "error, funcion matematica erronea" << endl;
				exit(0);
			}
		}

		// Guardo numeros con el signo menos como string, solo si: 
		else if (  (function[i]=='-' && i==0) ||
				   (function[i]=='-' && function[i-1]=='(') ||
				   (function[i]=='-' && is_operator(function[i-1])) ) {

			if (!parse_negative_number(function, string_array, string_array_size, i)){ 
				cout << "error, funcion matematica erronea" << endl;
				exit(0);
			}
		}

		// Guardo si es operador o parentesis: +-*/^()
		else if (  is_operator(function[i]) ||			// Si es operador O
				   is_parenthesis(function[i])  ) {		// es parentesis

			string aux_string = "";
			aux_string.append(1, function[i]);
			add_string_to_array(string_array, string_array_size, aux_string);
		}

		// Guardo la variable z y la j de imaginario
		else if (  function[i]=='z' ||			// Si es 'z' O
				   function[i]=='j'  ){			// si es 'j'

			string aux_string = "";
			aux_string.append(1, function[i]);
			add_string_to_array(string_array, string_array_size, aux_string);
		}
		i++;


	}
	
	return string_array;
}

// Comprueba la funcion matematica y la guarda en string array
bool parse_math_expression (const string function, string *& string_array, size_t & string_array_size, size_t & position){	
	string aux_string = "";

	while (function[position] != '(') {		// Estamos suponiendo que toda f mat es seguida con un '('

		if (position >= function.length()){ // Si la posicion se paso del largo, no encontro '('
			cout << "ERROR no encontro parentesis ( parseando"<< endl;
			exit (0);
		}

		aux_string.append(1, function[position]);	// Voy copiando letras
		position++;

	}

	position--;

	for (size_t i = 0; i< FUNCTIONS_AMOUNT; i++){	// Comparo contra el array de funciones a ver si 
		if (aux_string == math_functions[i]){		// esta bien escrita
			add_string_to_array(string_array, string_array_size, aux_string);
			return true;
		}
	}
	return false;
}

bool parse_number (const string function, string *& string_array, size_t & string_array_size, size_t & position){

	string aux_string = "";

	while(  isdigit(function[position]) ||		// Mientra lo q leo sea un digito O
			function[position] == '.' ||		// un punto O
			( (function[position] == 'e' || function[position] == 'E') && // (una 'e' seguida de un 
			  (function[position+1] == '-' || isdigit(function[position+1])) ) // signo menos o digito)
		 ) {

		aux_string.append(1, function[position++]);
	}

	position--;
	add_string_to_array(string_array, string_array_size, aux_string);
	return true;
}

bool parse_negative_number (const string function, string *& string_array, size_t & string_array_size, size_t & position){

	string aux_string = "";

	aux_string.append(1, function[position++]);	// Guarda el signo menos

	while(  isdigit(function[position]) ||	// Mientras sea digito O
			function[position] == '.' ) {	// sea un punt

		if (position >= function.length()){
			cout << "ERROR no encontro parentesis ( parseando"<< endl;
			return false;
		}
		aux_string.append(1, function[position++]);
	}
	position--;
	add_string_to_array(string_array, string_array_size, aux_string);
	return true;
}

// Comparo contra las iniciales de las funciones
bool is_math_function_initial (const char letter){
	size_t size = sizeof(functions_initials) / sizeof(functions_initials[0]);

	for (size_t i=0 ; i< size ; i++){
		if (letter == functions_initials[i]){
			return true;
		}
	}
	return false;
}

bool is_operator(char token){        
    return token == '+' || token == '-' ||      
           token == '*' || token == '/'	||
           token == '^' || token == 'e' ||
           token == 'E';      
}

bool is_parenthesis(char token){        
    return token == ')' || token == '(' ||
    	   token == ']' || token == '[' ||
    	   token == '{' || token == '}';      
} 

bool is_balanced (const string function){
	stk <char> stack;
	bool balanced = true;

	for (size_t i = 0; i < function.length() && balanced == true; ++i)
	{
		switch(function[i]){
			case '{':
			case '[':
			case '(':
				stack.push(function[i]);
				break;
			case '}':
				if (!stack.is_empty() && stack.peek() == '{')
					stack.pop();
				else
					balanced = false;
				break;
			case ']':
				if (!stack.is_empty() && stack.peek() == '[')
					stack.pop();
				else
					balanced = false;
				break;	
			case ')':
				if (!stack.is_empty() && stack.peek() == '(')
					stack.pop();
				else
					balanced = false;
				break;				
		}
	}
	if (!stack.is_empty())
		balanced = false;
	return balanced;
}


void add_string_to_array(string *& string_array, size_t & string_array_size, const string & str2add){

	resize_string_array(string_array, string_array_size, 1);

	string_array[string_array_size-1] = str2add;

}


bool resize_string_array (string *& string_array, size_t & string_array_size, size_t i){	// pido memoria para string array de tamaño i
	string * aux_string_array;

	if (string_array_size == 0){	// Primer caso
		string_array = new string [i];
		string_array[0]="";
		string_array_size += i;
		return true;
	}

	if (string_array_size>0){	// Luego del primer caso

		aux_string_array = new string [string_array_size]; // pido memoria para el string array aux

		for (size_t j = 0; j< string_array_size; j++){ // copio el string array a un auxiliar
			aux_string_array[j] = string_array [j];
		}

		delete[] string_array;
		string_array = new string [string_array_size+i];	// Pido memoria para i lugar mas

		for (size_t j = 0; j< string_array_size ; j++){ // recupero la informacion que tenia antes
			string_array[j] = aux_string_array [j];
		}

		for (size_t j = string_array_size; j < string_array_size+i; j++){	//Seteo las nuevas posiciones en vacio
			string_array[j] = "";
		}
		string_array_size += i;
		delete[] aux_string_array;

		return true;
	}

	return true;
}

bool check_operator_at_begining(const string function){

	if (function[0]=='*' || function[0]=='/' || function[0]=='^')
	{
		return false;
	}
	return true;
}