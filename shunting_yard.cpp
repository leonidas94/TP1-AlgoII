#include "shunting_yard.h"
#include <sstream>
#include <string>
#include "complejo.h"

/*#include <cmath>
#include <string>
#include "stk.h"*/
using namespace std; 

void shunting_yard(stk <string> & output_stack, string entered_function[],size_t tamano){
	//int counter = 0;

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


// Test if token is an pathensesis  
bool is_left_parenthesis(string token){        
    return token == "(" ||
    	   token == "[" ||
    	   token == "{";      
}   
bool is_right_parenthesis(string token){   

    return token == ")" ||
    	   token == "]" ||
    	   token == "}" ;    
}  

 
// Test if token is an operator        
bool is_operator(string token){        
    return token == "+" || token == "-" ||      
           token == "*" || token == "/"	||
           token == "^";      
}


bool is_math_function (string funct){

	bool aux;

	if (funct == "exp" || funct == "ln" ||
		funct == "re" || funct == "im" ||
		funct == "abs" || funct == "phase" ||
		funct == "sin" || funct == "cos")
	{
		aux = true;
	}
	else 
		aux = false;

	return aux;
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



bool is_string_digit (string str){

	if (str == "j")
		return true;

	string temp;
	stringstream ss (str); 
	double aux;
  
  	ss >> temp;
  	if(stringstream(temp) >> aux)  // Si puedo convertir a double
		return true;
	return false;
}


void solve_rpn(stk <string> & stack, complejo c){
	//cout<<"SOLVE RPN"<<endl;
	string temp;
	//double result;

	/*if (stack.is_empty()){
		return 0;
	}*/
	if (stack.is_empty())
	{
		cout<<"empty"<<endl;
		return;
	}
	else if (is_string_digit(stack.peek()))
	{
		if (stack.peek() == "j")
		{
			stack.pop();
			complejo x (0,1);
			string aux;
			aux = x.to_string();
			cout<<"El j es: "<<x<<endl;
			stack.push(aux);
		}
		return;
	}
	else if (stack.peek() == "z")
	{
		stack.pop();
		string aux;
		aux = c.to_string();
		stack.push(aux);
		return;
	}
	else if (is_operator(stack.peek())){
		string token = stack.peek();
		stack.pop();

		complejo x, y;
		double aux;


		solve_rpn(stack,c);
		string right = stack.peek();//solve_rpn(stack.peek());
		stack.pop();
		

		// i+d
		//   i+d
		/*if (right == "j")
		{
			x.set_img(1);
		}
		else if (right == "z")
		{
			x = c;
		}
		else{*/
			stringstream s1 (right); 
			/*s1 >> temp;
			stringstream(temp) >> x;//aux*/
			s1 >> x;
			//x.set_real(aux);
		//}
			//cout<<"Derecha: "<<x<<endl;

		string left;

		if (stack.is_empty())
		{
			left = "0";
		}
		else{
			solve_rpn(stack,c);
			left = stack.peek();// validar esto si no hay nada  que left sea 
			stack.pop();
		}

		/*if (left == "j")
		{
			y.set_img(1);
		}
		else if ( left == "z")
		{
			y = c;
		}
		else{*/
			stringstream s2 (left); 
			/*s2 >> temp;
			stringstream(temp) >> y;//auc*/
			s2 >> y;
			//y.set_real(aux);
		//}
		

		

		/*
		stringstream s2 (right);
		s2 >> temp; 
		stringstream(temp) >> y;*/

		//cout<<"left: "<<x<<"|right: "<<y<<endl;


		if 		(token == "+") x = y+x;
		else if (token == "-") x = y-x;
		else if (token == "*") x = y*x;
		else if (token == "^") x = y.complex_pow(x); // HACER OPERADOR ^ 
		else {
			if (x == 0)
			{
				cout<<"error division por 0"<<endl;
			}
			else
				x = y/x;
		}

		
		right = x.to_string();
		stack.push(right);
		return;
	}
	else if (is_math_function(stack.peek())){
		
		string function = stack.peek();
		stack.pop();

		solve_rpn(stack,c);
		string right = stack.peek();//solve_rpn(stack.peek());
		stack.pop();


		complejo y;
		double aux;
		if (right == "j")
		{
			y.set_img(1);
		}
		else if ( right == "z")
		{
			y = c;
		}else{
			stringstream s1 (right); 
			s1 >> temp;
			stringstream(temp) >> aux;
			y.set_real(aux);
		}

		if (function == "exp") y = y.exponencial();
		if (function == "ln") y = y.logaritmo();
		//if (function == "re") y = re(y);

		
		right = y.to_string();
		stack.push(right);
		return;
		
	}

} 
