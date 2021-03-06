#include "is_functions.h"

/* Para agregar funciones, modificar los dos vectores de funciones de abajo y modificar LA 
CANTIDAD EN IS_FUNCTIONS.H */
static char functions_initials[]= {'l', 'r', 'i', 'e', 'a', 'p', 'c', 's'};
static string math_functions[]= {"exp", "ln", "re", "im", "abs", "phase", "cos", "sin"};

// Compara contra las iniciales de las funciones
bool is_math_function_initial (const char letter){
	size_t size = sizeof(functions_initials) / sizeof(functions_initials[0]);

	for (size_t i=0 ; i< size ; i++){
		if (letter == functions_initials[i]){
			return true;
		}
	}
	return false;
}

// Se detecta si el numero es negativo
bool is_negative_number(const char actual, const char anterior, const char sig, size_t vuelta){
	if (
		  (actual=='-' && vuelta==0 && isdigit(sig)) 	 ||			 // Encuentro un menos Y esta al principio Y lo sig es un numero O
		  (actual=='-' && anterior=='(' && isdigit(sig)) ||			 // encuentro un menos Y el anterior es un parentesis abierto Y lo sig es un numero O
		  (actual=='-' && is_operator(anterior) && isdigit(sig))  ){ // encuentro un menos Y el anterior es un operador Y lo sig es un numero
		return true;
	}
	else return false;
}

// Se detecta si es una j negativa
bool is_negative_j(const char actual, const char anterior, const char sig, size_t vuelta){
	if (
		  (actual=='-' && vuelta==0 && sig == 'j') ||				 // Encuentro un menos Y esta al principio O
		  (actual=='-' && anterior=='(' && sig=='j') ||			 // encuentro un menos Y el anterior es un parentesis abierto O
		  (actual=='-' && is_operator(anterior) && sig=='j')  ){ // encuentro un menos Y el anterior es un operador
		return true;
	}
	else return false;
}

// Se detecta si es un operador para char
bool is_operator(char token){        
    return token == '+' || token == '-' ||      
           token == '*' || token == '/'	||
           token == '^' ;      
}


// Se detecta si es un operador para char
bool is_operator(string token){        
    return token == "+" || token == "-" ||      
           token == "*" || token == "/"	||
           token == "^";      
}


// Se detecta si es un paretensis
bool is_parenthesis(char token){        
    return token == ')' || token == '(' ||
    	   token == ']' || token == '[' ||
    	   token == '{' || token == '}';      
} 


// Se detecta si es un parentesis izquierdo
bool is_left_parenthesis(string token){        
    return token == "(" ||
    	   token == "[" ||
    	   token == "{";      
}

// Se detecta si es un parentesis derecho
bool is_right_parenthesis(string token){   

    return token == ")" ||
    	   token == "]" ||
    	   token == "}" ;    
}


// Se verifica si el operador tiene asociatividad izquierda
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


// Se detecta si es una funcion matematica
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

// Se verifica si una string es un digito o una j
bool is_string_digit (string str){

	if (str == "j" || str == "-j")
		return true;

	string temp;
	stringstream ss (str); 
	double aux;
  
  	ss >> temp;
  	if(stringstream(temp) >> aux){  // Si puedo convertir a double
		return true;
	}
	return false;
}