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
#include "extern.hpp"
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
	//Complex Driver to test seperate application and implementation files
	for (double i = 1; i < 10; ++ i)
	{
		Complex y{i * 2.7, i + 3.2};
		Complex z{i * 6, i + 8.3};

		Complex x;
		Complex k;

		std::cout << "Enter a complex number in the form: (a, b)\n? ";

		std::cin >> k; // demonstrating overloaded >>

		std::cout << "x: " << x << "\ny: " << y << "\nz: " << z << "\nk: "

					 << k << '\n'; // demonstrating overloaded <<

		x = y + z; // demonstrating overloaded + and =

		std::cout << "\nx = y + z:\n" << x << " = " << y << " + " << z << '\n';

		x = y - z; // demonstrating overloaded - and =

		std::cout << "\nx = y - z:\n" << x << " = " << y << " - " << z << '\n';

		x = y * z; // demonstrating overloaded * and =

		std::cout << "\nx = y * z:\n" << x << " = " << y << " * " << z << "\n\n";

		if (x != k) { // demonstrating overloaded !=

			std::cout << x << " != " << k << '\n';
		}

		std::cout << '\n';
		x = k;
		if (x == k) { // demonstrating overloaded ==
			std::cout << x << " == " << k << '\n';
		}

		std::cout << std::endl;
	}

	// driver to test namepaces and external linkage
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

//myNamespace2 greeting
void myNamespace2::myGreeting()
{
	std::cout << "Hello from myNamespace2!" << std::endl;
}

//myNamespace1 greeting
void myNamespace1::myGreeting()
{
	std::cout << "Hello from myNamespace1!" << std::endl;
}

//global namespace greeting
void theGreeting()
{
	std::cout << "Hello from the global namespace!" << std::endl;
}
