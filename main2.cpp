#include <iostream>
#include "stk.h"


using namespace std; 


// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){

	stk <int> stack;
	int i=1;
	stk <int> carlitos;

	cout<<"Esta vacia? : "<<stack.is_empty()<<endl;
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);

	carlitos = stack;
	cout<<"Tamano: "<<stack.stk_size()<<endl;
	while(!stack.is_empty()){
		cout<<"Valor: "<<stack.peek()<<endl;
		stack.pop();
	}
	while(!carlitos.is_empty()){
		cout<<"Valor car: "<<carlitos.peek()<<endl;
		carlitos.pop();
	}


	return 0;

}