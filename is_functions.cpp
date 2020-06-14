#include "is_functions.h"

/* Para agregar funciones, modificar los dos vectores de funciones de abajo y modificar LA 
CANTIDAD EN IS_FUNCTIONS.H */
static char functions_initials[]= {'l', 'r', 'i', 'e', 'a', 'p', 'c', 's'};
static string math_functions[]= {"exp", "ln", "re", "im", "abs", "phase", "cos", "sin"};

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

bool is_negative_number(const char actual, const char anterior, size_t vuelta){
	if (
		  (actual=='-' && vuelta==0) ||				 // Encuentro un menos Y esta al principio O
		  (actual=='-' && anterior=='(') ||			 // encuentro un menos Y el anterior es un parentesis abierto O
		  (actual=='-' && is_operator(anterior))  ){ // encuentro un menos Y el anterior es un operador
		return true;
	}
	else return false;
}

// Comparo contra operadores matematicos, en este caso recibe un char // VER QUE ONDA ACA LA E, LO DEJAMOS COMO OPERADOR O NO?
bool is_operator(char token){        
    return token == '+' || token == '-' ||      
           token == '*' || token == '/'	||
           token == '^' || token == 'e' ||
           token == 'E';      
}


// Comparo contra operadores matematicos, en este caso recibe una string
bool is_operator(string token){        
    return token == "+" || token == "-" ||      
           token == "*" || token == "/"	||
           token == "^";      
}


// Comparo contra parentesis, corchetes o llaves, recibe char
bool is_parenthesis(char token){        
    return token == ')' || token == '(' ||
    	   token == ']' || token == '[' ||
    	   token == '{' || token == '}';      
} 


// Comparo contra parentesis, corchete o llave izquierda
bool is_left_parenthesis(string token){        
    return token == "(" ||
    	   token == "[" ||
    	   token == "{";      
}


// Comparo contra parentesis, corchete o llave derecha
bool is_right_parenthesis(string token){   

    return token == ")" ||
    	   token == "]" ||
    	   token == "}" ;    
}


// Comparo si es asociativo a izquierda
bool is_left_associative(string token){
	bool left_assoc = true;

	if (token == "+" || token == "-" ||
		token == "*" || token == "/"){
		return left_assoc;
	}
	else if (token == "^"){
		left_assoc = false;
	}

	return left_assoc;
}


// Comparto si es una funcion matematica
bool is_math_function (string funct){

	bool aux;

	for (size_t i=0 ; i< FUNCTIONS_AMOUNT ; i++){
		if (funct == math_functions[i]){
			aux=true;
			return aux;
		}
	}
	return false;
}

bool is_string_digit (string str){

	if (str == "j")
		return true;

	string temp;
	stringstream ss (str); 
	double aux;
  
  	ss >> temp;
  	if(stringstream(temp) >> aux){  // Si puedo convertir a double
  		cout << aux;
		return true;
	}

	//stringstream s1 (right); 
	//s1 >> x;
	return false;
}