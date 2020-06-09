#include "stk.h"


// Test if token is an pathensesis  
bool is_left_parenthesis(char token){        
    return token == '(' ||
    	   token == '[' ||
    	   token == '{' ;      
}   
bool is_right_parenthesis(char token){        
    return token == ')' ||
    	   token == ']' ||
    	   token == '}';      
}    
 
// Test if token is an operator        
bool is_operator(char token){        
    return token == '+' || token == '-' ||      
           token == '*' || token == '/'	||
           token == '^';      
}

int precedence (char token){
	int p = 0;
	switch (token){
		case '+':
			p = 2;
			break;
		case '-':
			p = 2;
			break;
		case '*':
			p = 3;
			break;
		case '/':
			p = 3;
			break;
		case '^':
			p = 4;
			break;
	}
	return p;
} 


bool is_left_associative(char token){
	bool left_assoc = true;
	switch (token){
		case '+':
		case '-':
		case '*':
		case '/':
			break;
		case '^':
			left_assoc = false;
			break;
	}
	return left_assoc;
}


void shunting_yard(stk <char> & output_stack, string entered_function){
	int j = 0;

	stk <char> op_stack;
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
/*
void shunting_yard(string & string2fill){
  string aux_stack = "";

  for (size_t i=0 ; i < entered_function.length() ; i++){ // Saco los espacios
    if (entered_function[i] != SPACE_CHARACTER){
      aux_stack.append(1, entered_function[i]); // append (n, character): agrega n veces "character"
    }
  }*/


bool is_function (string funct){

	bool aux;

	if (funct == "exp" || funct == "ln" || funct == "re" || funct == "im" ||
		funct == "abs" || funct == "phase" || funct == "sin" || funct == "cos")
	{
		aux = true;
	}
	else 
		aux = false;

	return aux;
}

