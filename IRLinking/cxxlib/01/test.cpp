
#include <iostream>
#include "func1.hpp"

using namespace std;

int main(){

	func1 f;

	f.setFunc(1, 2);

	f.print();

	std::cout << "hello!";


	return 0;
}
