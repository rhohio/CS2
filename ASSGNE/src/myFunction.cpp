#include <iostream>
#include "myFunction.hpp"

/*Create myFunction.cpp: this function simply goes through all of the 
  characters in myArray (passed as an argument), and prints them 
  one by one. This output should be 1 2 3 4 5 6 7 8 9. Do this using 
  a for loop. You will use the SIZE constant variable as your upper bound 
  in your for loop. SIZE is not passed, and has external linkage. That 
  means that the variable is visible to the linker from other files, i.e. 
  it is “globally” visible and can be shared between translation units*/

void myFunction(char arr[])
{
	for(int i = 0; i < SIZE; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}