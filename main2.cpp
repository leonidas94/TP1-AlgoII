#include <iostream>
#include "stk.h"


using namespace std; 


// **********************************MAIN**********************************//

int main(int argc, char * const argv[]){

	stk <int> stack;
	int i=0;

	cout<<"Esta vacia? : "<<stack.is_empty()<<endl;
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	stack.push(i++);
	cout<<"Tamano: "<<stack.stk_size()<<endl;
	while(!stack.is_empty()){
		cout<<"Valor: "<<stack.peek()<<endl;
		stack.pop();
	}
	stack.pop();


	return 0;

}