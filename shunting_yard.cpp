#include "shunting_yard.h"

using namespace std; 

void shunting_yard(stk <string> & output_stack, string entered_function[],size_t tamano){

	stk <string> op_stack; // Operator stack

	string aux;

	for (int i = 0; i < (int)tamano; ++i)
	{
		
		if (is_string_digit(entered_function[i]) ||  entered_function[i]=="z")
		{	

			output_stack.push(entered_function[i]);
		}
		else if(is_math_function(entered_function[i])) {

			op_stack.push(entered_function[i]);
		}	
		
		else if (is_operator(entered_function[i]))
		{
	
			//Calcular la precedencia antes
			op_stack.peek(aux);

			while((!op_stack.is_empty() && is_operator(aux)) && 
				((precedence(entered_function[i]) < precedence(aux)) || ((precedence(entered_function[i]) == precedence(aux)) && is_left_associative(entered_function[i])))
				 && (!is_left_parenthesis(aux)))
			{

				output_stack.push(aux);
				op_stack.pop();

				if(!op_stack.peek(aux)){
					//cout << "Error. Peek2." << endl;
					//exit(1);
				}
			}
			op_stack.push(entered_function[i]);
			
		}
		else if (is_left_parenthesis(entered_function[i]))
		{
			op_stack.push(entered_function[i]);
		}  
		else if (is_right_parenthesis(entered_function[i]))
		{
			if(!op_stack.peek(aux)){
				cout << "Error. Peek3." << endl;
				exit(1);
			}

			while ( !is_left_parenthesis(aux) ){
				
				output_stack.push(aux);
				op_stack.pop();
				op_stack.peek(aux);

			}
			if(!op_stack.peek(aux)){
				cout << "Error. Peek5." << endl;
				exit(1);
			}
			if (is_left_parenthesis(aux))
			{
				op_stack.pop();
				
				op_stack.peek(aux);

				if (is_math_function(aux)){

					output_stack.push(aux);
					op_stack.pop();
				}
			}
		}


	}
	while(!op_stack.is_empty()){

		if(!op_stack.peek(aux)){
			cout << "Error. Peek8." << endl;
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
// c, que será reemplazado por z.
void solve_rpn(stk <string> & stack, complejo c){
	string temp;
	string aux;

	if (stack.is_empty())	// Caso base
	{
		cerr << "Stack is empty." << endl;
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
			cerr << "Error. Peek9" << endl;
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
			cerr << "Error. Peek10" << endl;
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
				cerr << "Error. Peek11" << endl;
				exit(1);	
			} 
			
			stack.pop();
		}

		stringstream s2 (left); 
		s2 >> y;

		if 		(token == "+") x = y+x;
		else if (token == "-") x = y-x;
		else if (token == "*") x = y*x;
		else if (token == "^") x = y.complex_pow(x); 
		else if (token == "/"){
			if (x == 0)
			{
				cerr << "Error. Division por 0." << endl;
				exit(1);
			}
			else
				x = y/x;
		}

		
		right = x.to_string();
		stack.push(right);
		return;
	}
	else if (stack.peek(aux) && is_math_function(aux)){
		
		string function;

		if(!stack.peek(function)){
			cerr << "Error. Peek12" << endl;
			exit(1);
		}

		stack.pop();

		solve_rpn(stack,c);

		string right;
		if(!stack.peek(right)){
			cerr << "Error. Peek13" << endl;
			exit(1);
		}
		stack.pop();


		complejo y;


		stringstream s1 (right); 
		s1 >> y;


		if      (function == "exp")   y = y.exponencial();
		else if (function == "ln") 	  y = y.logaritmo();
		else if (function == "re") 	  y = y.re();
		else if (function == "im") 	  y = y.im();
		else if (function == "abs")   y = y.get_abs();
		else if (function == "phase") y = y.get_phase();


		
		right = y.to_string();
		stack.push(right);
		return;
		
	}

} 
