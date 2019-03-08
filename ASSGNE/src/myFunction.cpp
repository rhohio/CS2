#include <iostream>
#include "myFunction.hpp"
#include "extern.hpp"

void myFunction(char arr[])
{
	for(int i = 0; i < SIZE; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}