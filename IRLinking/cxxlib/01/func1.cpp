
#include "func1.hpp"

bool func1::setFunc(int a, int b){

	this->a = a;
	this->b = b;

	return true;
}

bool func1::print(){

	cout << "print: " << a << " " << b << endl;

	return true; 
}
