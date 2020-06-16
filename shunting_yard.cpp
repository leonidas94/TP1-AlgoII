#include "shunting_yard.h"

using namespace std; 

void shunting_yard(stk <string> & output_stack, string entered_function[],size_t tamano){

	stk <string> op_stack;
	stk <string> tokens_stack; // Lo voy a usar para tratar de separar entered_function en tokens

// ACA ARRANCA EL AGLORITMO
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

			while((!op_stack.is_empty() && is_operator(op_stack.peek())) && 
				((precedence(entered_function[i]) < precedence(op_stack.peek())) || ((precedence(entered_function[i]) == precedence(op_stack.peek())) && is_left_associative(entered_function[i])))
				 && (!is_left_parenthesis(op_stack.peek())))
			{
				output_stack.push(op_stack.peek());
				op_stack.pop();
			}
			op_stack.push(entered_function[i]);
			
		}
		else if (is_left_parenthesis(entered_function[i]))
		{
			op_stack.push(entered_function[i]);
		}  
		else if (is_right_parenthesis(entered_function[i]))
		{
			
			while (!is_left_parenthesis(op_stack.peek())){
				output_stack.push(op_stack.peek());
				op_stack.pop();
			}
			if (is_left_parenthesis(op_stack.peek()))
			{
				op_stack.pop();
				if (is_math_function(op_stack.peek())){
					output_stack.push(op_stack.peek());
					op_stack.pop();
				}
			}
		}


	}
	while(!op_stack.is_empty()){
		output_stack.push(op_stack.peek());
		op_stack.pop();		
	}
}


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


void solve_rpn(stk <string> & stack, complejo c){
	string temp;

//cout << "entra al slve" << endl;
	if (stack.is_empty())	// Caso base
	{
		cerr << "Stack is empty." << endl;
		return;
	}

	else if (is_string_digit(stack.peek()))
	{
		//cout << "digitox" << endl;
		if (stack.peek() == "j")
		{
			stack.pop();
			complejo x (0,1);
			stack.push(x.to_string());
		}
		return;
	}

	else if (stack.peek() == "z")
	{
		//cout << "zetax" << endl;
		stack.pop();
		stack.push(c.to_string());
		return;
	}

	else if (is_operator(stack.peek())){

		//cout << "operadorx" << endl;
		string token = stack.peek();
		stack.pop();

		complejo x, y;

		solve_rpn(stack,c);
		string right = stack.peek();
		stack.pop();
		
		stringstream s1 (right); 
		s1 >> x;
		
		string left;

		if (stack.is_empty()){

			left = "0";
		}
		else{

			solve_rpn(stack,c);
			left = stack.peek(); 
			stack.pop();
		}

		stringstream s2 (left); 
		s2 >> y;
		//cout<<"ESTO ES y: "<<y<<endl;

		if 		(token == "+") x = y+x;
		else if (token == "-") x = y-x;
		else if (token == "*") x = y*x;
		else if (token == "^") x = y.complex_pow(x);// HACER OPERADOR ^ 
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
	else if (is_math_function(stack.peek())){
		
		//cout << "funcionx" << endl;
		string function = stack.peek();
		stack.pop();

		solve_rpn(stack,c);
		string right = stack.peek();//solve_rpn(stack.peek());
		stack.pop();


		complejo y;


		stringstream s1 (right); 
		s1 >> y;


		if      (function == "exp")   y = y.exponencial();
		else if (function == "ln") 	  y = y.logaritmo();
		else if (function == "re") 	  y = y.re();
		else if (function == "im") 	  y = y.im();
		else if (function == "abs")   y = complejo(y.get_abs(),0);
		else if (function == "phase") y = complejo(y.get_phase(),0);


		
		right = y.to_string();
		stack.push(right);
		return;
		
	}

} 
