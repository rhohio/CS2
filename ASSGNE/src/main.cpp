/*
   COPYRIGHT (C) 2017 Student Name (UANET ID ) All rights reserved.
   CSII Assignment E
   Author.  Kyle Dabbieri
            kad1445@zips.uakron.edu
   Version. 1.01 03.06.2019
   Purpose: Splitting classes into hpp and cpp files, namepaces
*/
#include "Complex.hpp"
#include "myFunction.hpp"
#include <iostream>

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

	myFunction(myArray);

	{
		using namespace myNamespace2;
		myGreeting();
	}

	{
		using namespace myNamespace1;
		myGreeting();
	}

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
