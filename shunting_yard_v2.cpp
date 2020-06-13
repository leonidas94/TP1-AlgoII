#include "shunting_yard_v2.h"
#include <sstream>
#include <string>

/*#include <cmath>
#include <string>
#include "stk.h"*/
using namespace std; 

void shunting_yard2(stk <string> & output_stack, string entered_function[],size_t tamano){
	//int counter = 0;

	stk <string> op_stack;

	stk <string> tokens_stack; // Lo voy a usar para tratar de separar entered_function en tokens

	
	
	//cout<<tamano<<endl;
// ACA ARRANCA EL AGLORITMO
	for (int i = 0; i < (int)tamano; ++i)
	{
		if (isdigit(entered_function[i]) ||  entered_function[i]=="z")
		{	
			output_stack.push(entered_function[i]);

			//cout<<"Numero: "<<entered_function[i]<<endl;
		}
		else if(is_function(entered_function[i])) {
			op_stack.push(entered_function[i]);
		}	
		//const string token (1, entered_function[i]);
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
			//cout<<entered_function[i]<<endl;
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


bool is_function (string funct){

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

bool isdigit (string str){

	string temp;
	stringstream ss (str); 
	double aux;
  
  	ss >> temp;
  	if(stringstream(temp) >> aux)  // Si puedo convertir a double
		return true;
	return false;
}


void solve_rpn(stk <string> & stack){
	cout<<"SOLVE RPN"<<endl;
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
	else if (isdigit(stack.peek()))
	{
		return;
	}
	else if (is_operator(stack.peek())){
		string token = stack.peek();
		stack.pop();

		solve_rpn(stack);
		string right = stack.peek();//solve_rpn(stack.peek());
		stack.pop();
		

		solve_rpn(stack);
		string left = stack.peek();//solve_rpn(stack);
		stack.pop();
		cout<<"derecha"<<left<<endl;
		//cout<<"leyo el de la izquierda"<<endl;
		double x, y;

		stringstream s1 (left); 
		s1 >> temp;
		stringstream(temp) >> x;
		stringstream s2 (right);
		s2 >> temp; 
		stringstream(temp) >> y;

		cout<<"left: "<<x<<"|right: "<<y<<endl;


		if 		(token == "+") x += y;
		else if (token == "-") x -= y;
		else if (token == "*") x *= y;
		else if (token == "^") x = pow(x,y);
		else {
			if (y==0)
			{
				cout<<"error division por 0"<<endl;
			}
			else
				x /= y;
		}

		ostringstream x_convert;
		x_convert << x;
		cout<<x<<endl;
		right = x_convert.str();
		stack.push(right);
		return;
	}
	else if (is_function(stack.peek())){
		string function = stack.peek();
		stack.pop();

		solve_rpn(stack);
		string right = stack.peek();//solve_rpn(stack.peek());
		stack.pop();

		double y;
		stringstream s1 (right);
		s1 >> y; 
		cout<<y<<endl;

		if (function == "exp") y = exp(y);
		if (function == "ln") y = log(y);

		ostringstream y_convert;
		y_convert << y;
		cout<<y<<endl;
		right = y_convert.str();
		stack.push(right);
		return;
		
	}

} 



