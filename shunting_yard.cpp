#include "shunting_yard.h"

using namespace std; 

void shunting_yard(stk <string> & output_stack, string entered_function[],size_t tamano){

	stk <string> op_stack; // Donde se almacenaran los operadores

	string aux;

	for (int i = 0; i < (int)tamano; ++i) // Para cada token parseado anteriormente
	{
		
		if (is_string_digit(entered_function[i]) ||  entered_function[i]=="z")  // Se fija si es un numero o una z para ponerlo en el 
		{																		// output stack
			output_stack.push(entered_function[i]);
		}
		else if(is_math_function(entered_function[i])) 
		{																		// Se fija si es una funcion para ponerlo en operator stack
			op_stack.push(entered_function[i]);
		}	
		
		else if (is_operator(entered_function[i]))
		{
			op_stack.peek(aux);

			bool lower_precedence = precedence(entered_function[i]) < precedence(aux);	// Se determina si el token tiene menor precedencia que el ultimo en el stack
			bool equal_precedence =precedence(entered_function[i]) == precedence(aux);	// Se determina si el token tiene igual precedencia que el ultimo en el stack

			
			while((!op_stack.is_empty() && is_operator(aux)) && 
				(lower_precedence || ( equal_precedence && is_left_associative(entered_function[i])))
				 && (!is_left_parenthesis(aux)))
			{

				output_stack.push(aux); 										// Se pasa al operador o funcion al output stack
				op_stack.pop();													// Se desapila el operador

				op_stack.peek(aux);

				lower_precedence = precedence(entered_function[i]) < precedence(aux); // Se determina si el token tiene menor precedencia que el ultimo en el stack
				equal_precedence =precedence(entered_function[i]) == precedence(aux); // Se determina si el token tiene igual precedencia que el ultimo en el stack
			}
			op_stack.push(entered_function[i]);						// Se apila el nuevo operador en la pila de operadores
			
		}
		else if (is_left_parenthesis(entered_function[i]))
		{
			op_stack.push(entered_function[i]);
		}  
		else if (is_right_parenthesis(entered_function[i]))
		{
			if(!op_stack.peek(aux)){
				cout << "Error. Stack is empty." << endl;
				exit(1);
			}

			while ( !is_left_parenthesis(aux) ){					// Mientras que no sea un parentesis dereche se pasan los operadores 
																	// al output_stack
				output_stack.push(aux);										
				op_stack.pop();
				op_stack.peek(aux);

			}
			if(!op_stack.peek(aux)){
				cout << "Error. Stack is empty." << endl;
				exit(1);
			}
			if (is_left_parenthesis(aux))
			{
				op_stack.pop();
				
				op_stack.peek(aux);

				if (is_math_function(aux)){							// En caso de que sea una funcion se la pasa al output_stack

					output_stack.push(aux);
					op_stack.pop();
				}
			}
		}


	}
	while(!op_stack.is_empty()){									// Se pasan todos los operadores a el output_stack

		if(!op_stack.peek(aux)){
			cout << "Error. Stack is empty." << endl;
			exit(1);
		}
		output_stack.push(aux);
		op_stack.pop();		
	}
}

// Esta funcion devuelve la presedencia del operador que se le pasa por copia
int precedence (string token){
	int p = 0;

	if (token == "+" || token == "-")
		p=2;
	else if (token == "*" || token == "/")
		p=3;
	else if (token == "^")
		p=4;

	return p;
} 

// Esta funcion resulve la funcion en notacion polaca inversa. Recibe el stack con la funcion y el complejo
// c, que será reemplazado por z. Es importante remarcar que el resultado lo devuelve en el stack
void solve_rpn(stk <string> & stack, complejo c){
	string temp;
	string aux;

	if (stack.is_empty())	// Caso base
	{
		return;
	}

	else if (stack.peek(aux) && is_string_digit(aux)) 	// Se fija si es un numero o una j se crea el numero complejo
	{
		if (stack.peek(aux) && aux == "j")				// Complejo puro positivo
		{
			stack.pop();
			complejo x (0,1);
			stack.push(x.to_string());
		}		
		if (stack.peek(aux) && aux == "-j")				// Complejo puro negativo
		{
			stack.pop();
			complejo x (0,-1);
			stack.push(x.to_string());
		}
		return;
	}

	else if (stack.peek(aux) && aux == "z")			// Se fija si es una z y la reemplaza por c
	{
		stack.pop();
		stack.push(c.to_string());
		return;
	}

	else if (stack.peek(aux) && is_operator(aux)){	// Se fija si es un operardor

		string token;
		if(!stack.peek(token)){						// Se guarda el operador en token
			cerr << "Error. Stack is empty." << endl;
			exit(1);
		}

		stack.pop();								// Se quita el operador de la pila

		complejo x, y;

		solve_rpn(stack,c);							// Como todos los operadores son binarios reciben un elemento a izquierda
													// y otro a derecha, por lo tanto se llama recursivamente a solve_rpn
													// y se guarda lo que retorna en la cima de la pila a la variable right 
													// (elemento de la derecha de la operacion)
		
		string right;

		if(!stack.peek(right)){						// Se valida que haya algo en el stack
			cerr << "Error. Stack is empty." << endl;
			exit(1);
		}

		stack.pop();								// Se quita el valor del stack
		
		stringstream s1 (right); 
		s1 >> x;									// Se combierte al valor a un numero complejo
		
		string left;

		if (stack.is_empty()){						// Si no hay elemento a izquierda significa que la funcion comienza 
													// - o +, y de ser asi se le asigna 0 al elemento de la izquierda
			left = "0";
		}
		else{

			solve_rpn(stack,c);						// Se llama recursivamente para obtener el valor a izquierda del operador

			if(!stack.peek(left)){
				cerr << "Error. Stack is empty." << endl;
				exit(1);	
			} 
			
			stack.pop();
		}

		stringstream s2 (left); 					// Se combierte el operando de la izaquierda a complejo
		s2 >> y;
													// Segun que operador se desea aplicar se hace la cuenta
		if 		(token == "+") x = y+x;
		else if (token == "-") x = y-x;
		else if (token == "*") x = y*x;
		else if (token == "^") x = y.complex_pow(x); 
		else if (token == "/"){						// Se valida de que no se divida por cero
			if (x == 0)
			{
				cerr << "Error. Division por 0." << endl;
				exit(1);
			}
			else
				x = y/x;
		}

		
		right = x.to_string();						// El resultado obtenido se lo combierte a string para 
		stack.push(right);							// pushearlo en el stack
		return;
	}
	else if (stack.peek(aux) && is_math_function(aux)){
													// Se fija si es una funcion matematica de un solo operando
		string function;

		if(!stack.peek(function)){
			cerr << "Error. Stack is empty." << endl;
			exit(1);
		}

		stack.pop();								// Se quita la funcion del stach

		solve_rpn(stack,c);							// Se obtiene recursivamente el operando de la funcion

		string right;
		if(!stack.peek(right)){
			cerr << "Error. Stack is empty." << endl;
			exit(1);
		}
		stack.pop();								// Se saca este numero del stack para ser evaluado


		complejo y;


		stringstream s1 (right); 					// Se combierte al string que estaba en el stack (el numero)
		s1 >> y;									// a un numero complejo para evaluarlo en la funcion

													// Segun la funcion requerida se evalua el numero
		if      (function == "exp")   y = y.exponencial();
		else if (function == "ln") 	  y = y.logaritmo();
		else if (function == "re") 	  y = y.re();
		else if (function == "im") 	  y = y.im();
		else if (function == "abs")   y = complejo(y.get_abs(),0);
		else if (function == "phase") y = complejo(y.get_phase(),0);


		right = y.to_string();						// Se combierte al resultado en un string para 
		stack.push(right);							// pusheralo en el stack
		return;
		
	}

} 
