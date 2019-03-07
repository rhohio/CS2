/*
   COPYRIGHT (C) 2017 Student Name (UANET ID ) All rights reserved.
   CSII Assignment E
   Author.  Kyle Dabbieri
            kad1445@zips.uakron.edu
   Version. 1.01 03.06.2019
   Purpose: Splitting classes into hpp and cpp files, namepaces
*/
#include "Complex.hpp"
#include "Complex.cpp"
#include "myFunction.cpp"
#include "myFunction.hpp"
#include <iostream>



namespace
{
	extern const int SIZE = 10;
}

void myFunction(char []);

namespace myNamespace1
{
	void myGreeting();
}


namespace myNamespace2
{
	void myGreeting();
}

void theGreeting();

int main()
{
	char myArray[SIZE] = "123456789";

	// call your function using only the array
	// to demonstrate the SIZE is sharable (external)

	myFunction(myArray);

	// call your second namespace greeting function

	{
		using namespace myNamespace2;

		myGreeting();
	}

	// call your first namespace greeting function

	{
		using namespace myNamespace1;

		myGreeting();
	}

	// call your first namespace greeting function

	theGreeting();

	return 0;
}


void myNamespace2::myGreeting()
{
	std::cout << "Hello from myNamespace2!" << std::endl;
}

void myNamespace1::myGreeting()
{
	std::cout << "Hello from myNamespace1!" << std::endl;
}

void theGreeting()
{
	std::cout << "Hello from the global namespace!" << std::endl;
}
