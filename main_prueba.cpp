#include <iostream>
#include <string>
#include "str.h"

using namespace std;  

int main (){

	str entered_function = "81.5+18+sin"; //
	//cout<<entered_function<<endl;
	str * aux_str;
	aux_str = new str [2];

	cout<<"llegue"<<endl;
	aux_str[0]=entered_function;
	aux_str[1]='c';
	cout<<"pase"<<endl;

	int tamano = sizeof(aux_str)/sizeof(aux_str[0]);

	cout<<tamano<<endl;
/*	int i = 0;
	while ( i<entered_function.length()){	//trato de separar en tokens (1.5, exp...)
		
		int j = 0;
		//if (isdigit(entered_function[i]))
		//{

		if (entered_function[i]=='s' || entered_function[i]=='c') 
		{
			while(entered_function[i]!='(')
			{
				if (i>entered_function.length())
				{
					
					cout <<"error"<<endl;
					//return;
				}
				aux_str.my_str[j++]=entered_function[i++];
				

			}
			cout<<aux_str<<endl;
			if (aux_str.compare("sin")!=0 || aux_str == "cos")
			{
				cout<<"guardar en arreglo de string"<<endl;
				cout<<aux_str<<endl;
			}
		}
			
		else if (entered_function[i]== '.' || isdigit(entered_function[i]))
		{
			//cout<<entered_function[i]<<endl;
			while(isdigit(entered_function[i]) || entered_function[i] == '.' || 
				(entered_function[i] == 'e' || entered_function[i] == 'E' &&  (entered_function[i+1] == '-' || isdigit(entered_function[i+1]))))
			{
				//cout<<"en el while"<<endl;
				if (i>entered_function.length())
				{
					
					//cout <<"error"<<endl;
					//return;
				}
				//cout<<"antes de asignar"<<endl;
				aux_str.my_str[j++]=entered_function[i++];
				//cout<<"despues de asignar"<<endl;

			}
			//cout<<"es: "<<entered_function[i]<<endl;
			cout<<aux_str<<endl;
			//cout<<"i: "<<i<<"|   j: "<<j<<endl;
		}
		else{
			i++;
		}


		//}
		//cout<<aux_str<<endl;
	}*/
	

	return 0;
}