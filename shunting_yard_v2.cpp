#include "stk.h"
#include "shunting_yard_v2.h"

void shunting_yard(stk <str> & output_stack, string entered_function){
	int counter = 0;

	stk <str> op_stack;

	stk <str> tokens_stack; // Lo voy a usar para tratar de separar entered_function en tokens

	for (int i = 0; i<entered_function.length(); ++i){	//trato de separar en tokens (1.5, exp...)
		str aux_str;


	}

	for (int i = 0; i < entered_function.length(); ++i)
	{
		if (entered_function[i]!=' ')
		{
			/*output_queue[j]=entered_function[i];
			cout<<"Es:"<<output_queue[j]<<"|"<<endl;
			j++;*/

		}
		if (isdigit(entered_function[i]) || entered_function[i]=='z')
		{	
			
			output_stack.push(entered_function[i]);
			//cout<<"Numero: "<<entered_function[i]<<endl;
		}
		//const string token (1, entered_function[i]);
		else if (is_operator(entered_function[i]))
		{
			while((!op_stack.is_empty() && is_operator(op_stack.peek())) && 
				((precedence(entered_function[i]) < precedence(op_stack.peek())) || ((precedence(entered_function[i]) == precedence(op_stack.peek())) && is_left_associative(entered_function[i])))
				 &&(!is_left_parenthesis(op_stack.peek())))
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
bool is_left_parenthesis(str token){        
    return token.compare("(") ||
    	   token.compare("[") ||
    	   token.compare("{") ;      
}   
bool is_right_parenthesis(str token){        
    return token.compare(")") ||
    	   token.compare("]") ||
    	   token.compare("}") ;    
}  

 
// Test if token is an operator        
bool is_operator(str token){        
    return token.compare("+") || token.compare("-") ||      
           token.compare("*") || token.compare("/")	||
           token.compare("^");      
}


int precedence (str token){
	int p = 0;

	if (token.compare("+") || token.compare("-"))
		p=2;
	if (token.compare("*") || token.compare("/"))
		p=3;
	if (token.compare("^"))
		p=4;

	return p;
} 


bool is_left_associative(str token){
	bool left_assoc = true;

	if (token.compare("+") || token.compare("-") ||
		token.compare("*") || token.compare("/")){
		return left_assoc;
	}
	if (token.compare("^")){
		left_assoc = false;
	}

	return left_assoc;
}


bool is_function (str funct){

	bool aux;

	if (funct.compare("exp") || funct.compare("ln") ||
		funct.compare("re") || funct.compare("im") ||
		funct.compare("abs") || funct.compare("phase") ||
		funct.compare("sin") || funct.compare("cos"))
	{
		aux = true;
	}
	else 
		aux = false;

	return aux;
}

