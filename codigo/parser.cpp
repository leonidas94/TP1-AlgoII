#include "parser.h"

using namespace std;

// Se parsea la funcion ingresada
string * parse_function(const string function, size_t & string_array_size){
	size_t i = 0;
	string * string_array;				

	if (!check_balance (function)){				// Se valida que la expresion este balanceada
		cerr << "Error. No esta balanceada" << endl;
		exit(0);
	}
	if (!check_operator_at_begining(function)){	// Se valida que la funcion no comience con un operador * o /
		cerr << "Error, no puede comenzar con " << function[0] << endl;
		exit(0);
	}
	if(!check_syntax(function)){
		cerr << "Error, sintaxis " << endl;
		exit(0);
	}

	while (i < function.length()){				// Se recorre el string de entrada

		// Se guardan las expresiones matematicas (exp, ln, phase, abs, re, im)
		if (  is_math_function_initial(function[i]) &&	// Si es la inicial de una funcion matematica y
			  function[i+1]!='-' &&						// si el siguiente no es un guion y
			  !isdigit(function[i+1])  ){				// si el siguiente no es un digito

			if (!parse_math_expression(function, string_array, string_array_size, i)){
				cerr << "Error. Funcion matematica erronea." << endl;					
				exit(0);
			}
		}

		else if (function[i] == ' '){}

		// Guardo numeros o numeros que empiecen con punto
		else if (  isdigit(function[i]) ||							// Si es un digito o
				   (function[i]=='.' && isdigit(function[i+1]))  ){ // es un punto Y el siguiente un digito

			if (!parse_number(function, string_array, string_array_size, i)){ // Trato de parsear el numero
				cerr << "Error. Formato número." << endl;
				exit(0);
			}
		}

		// Guardo numeros con el signo menos como string: 
		else if ( is_negative_number(function[i], function[i-1], function[i+1], i) ) {

			if (!parse_negative_number(function, string_array, string_array_size, i)){ 
				cerr << "Error. Formato número negativo." << endl;
				exit(0);
			}
		}

		else if ( is_negative_j(function[i], function[i-1], function[i+1], i) ) {
			
			if (!parse_negative_j(function, string_array, string_array_size, i)){ 
				cerr << "Error. Formato j." << endl;
				exit(0);
			}
		}

		// Guardo si es operador o parentesis: +-*/^()
		else if (  is_operator(function[i]) ||			// Si es operador o
				   is_parenthesis(function[i])  ) {		// es parentesis

			string aux_string = "";
			aux_string.append(1, function[i]);
			add_string_to_array(string_array, string_array_size, aux_string);
		}

		// Guardo la variable z y la j de imaginario
		else if (  function[i]=='z' ||			// Si es 'z' o
				   function[i]=='j' ){			// si es 'j'

			string aux_string = "";
			aux_string.append(1, function[i]);
			add_string_to_array(string_array, string_array_size, aux_string);
		}

		else {
			cerr << "Error. Caracter invalido." << endl;
			exit(0);
		}
		i++;
	}

for (size_t j=0 ; j<string_array_size ; j++){
cout << string_array[j] << endl;
}
	return string_array;
}


// Comprueba la funcion matematica y la guarda en string array
bool parse_math_expression (const string function, string *& string_array, size_t & string_array_size, size_t & position){	
	string aux_string = "";

	while (function[position] != '(') {		// Todas las funciones matematicas terminan con '('

		if (position >= function.length()){ // Si la posicion supero a el largo de la string
			cerr << "Error. No encontro parentesis ( parseando." << endl;
			exit (0);
		}

		aux_string.append(1, function[position]);	// Se copia letra por letra
		position++;
	}
	position--;

	if (is_math_function(aux_string)){	// Se verifica que sea una funcion
		add_string_to_array(string_array, string_array_size, aux_string);
		return true;
	}
	return false;
}


// Se parsea el numero
bool parse_number (const string function, string *& string_array, size_t & string_array_size, size_t & position){

	string aux_string = "";

	while(  isdigit(function[position]) ||																	// Mientra lo q leo sea un digito ||
			function[position] == '.' ||																	// un punto ||
			(function[position] == '-' && ((function[position-1] == 'e' || function[position-1] == 'E')))||	// un signo - precedido por una e ||
			( (function[position] == 'e' || function[position] == 'E') && 	    							// (una 'e' seguida de un 
			  (function[position+1] == '-' || isdigit(function[position+1])) )  							// signo menos o digito)
		 ) {
		aux_string.append(1, function[position++]);
	}

	position--;
	add_string_to_array(string_array, string_array_size, aux_string);
	return true;
}


// Se pasea el numero negativo y se lo guarda
bool parse_negative_number (const string function, string *& string_array, size_t & string_array_size, size_t & position){

	string aux_string = "";

	aux_string.append(1, function[position++]);	// Guarda el signo menos

	while(  isdigit(function[position]) ||	// Mientras sea digito ||
			function[position] == '.' ) {	// sea un punto

		if (position >= function.length()){
			cerr << "Error. No encontro parentesis ( parseando." << endl;
			return false;
		}
		aux_string.append(1, function[position++]);
	}
	position--;
	add_string_to_array(string_array, string_array_size, aux_string);
	return true;
}


// Se parsea la j negativa
bool parse_negative_j (const string function, string *& string_array, size_t & string_array_size, size_t & position){

	string aux_string = "";

	aux_string.append(1, function[position++]);	// Guarda el signo menos
	aux_string.append(1, function[position++]);

	position--;
	add_string_to_array(string_array, string_array_size, aux_string);
	return true;
}


// Funcion que agrega una string a string_array
void add_string_to_array(string *& string_array, size_t & string_array_size, const string & str2add){

	resize_string_array(string_array, string_array_size, 1);

	string_array[string_array_size-1] = str2add;

}


// Funcion que le agrega i lugares a string_array
bool resize_string_array (string *& string_array, size_t & string_array_size, size_t i){	// pido memoria para string array de tamaño i
	string * aux_string_array;

	if (string_array_size == 0){	// Primer caso
		string_array = new string [i];
		string_array_size += i;
		return true;
	}

	else if (string_array_size>0){	// Luego del primer caso

		aux_string_array = new string [string_array_size]; // Pido memoria para el string array aux

		for (size_t j = 0; j< string_array_size; j++){ // Copio el string array a un auxiliar
			aux_string_array[j] = string_array [j];
		}

		delete[] string_array;
		string_array = NULL;
		
		string_array = new string [string_array_size +i ];	// Pido memoria para i lugar mas

		for (size_t j = 0; j< string_array_size ; j++){ // Recupero la informacion que tenia antes
			string_array[j] = aux_string_array [j];
		}

		//for (size_t j = string_array_size; j < string_array_size+i; j++){	// Seteo las nuevas posiciones en vacio
		//	string_array[j] = "";
		//}
		string_array_size += i;

		delete[] aux_string_array;
		aux_string_array = NULL;

		return true;
	}

	return true;
}


// Funcion que verifica la expresion esta balanceada
bool check_balance (const string function){
	stack <char> stack;
	bool balanced = true;
	char aux;

	for (size_t i = 0; i < function.length() && balanced == true; ++i)
	{
		switch(function[i]){
			case '{':
			case '[':
			case '(':
				stack.push(function[i]);
				break;
			case '}':
				if (!stack.is_empty() && (stack.peek(aux) && aux == '{'))
					stack.pop();
				else
					balanced = false;
				break;
			case ']':
				if (!stack.is_empty() && (stack.peek(aux) && aux == '['))
					stack.pop();
				else
					balanced = false;
				break;	
			case ')':
				if (!stack.is_empty() && (stack.peek(aux) && aux == '('))
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


// Funcion que checkea que lo ingresado no haya empezado con un operador matamatico prohibido
bool check_operator_at_begining(const string function){

	if (function[0]=='*' || function[0]=='/' || function[0]=='^')
	{
		return false;
	}
	return true;
}

bool check_syntaxis(const string function){
	for (size_t i=0; i < function.length(); i++){
		if(is_operator(function[i]))
	}
}