/*
   COPYRIGHT (C) 2017 Student Name (UANET ID ) All rights reserved.
   CSII Assignment C
   Author.  Kyle Dabbieri
            kad1445@zips.uakron.edu
   Version. 1.01 02.14.2019
   Purpose: This program is the test cases for the assignment
*/

#include <iostream>
#include <string>
#include <sstream> // for ostringstream class

/*
    Modify the class to enable input and output of complex numbers via overloaded + and - operators, respectively (addition and subtraction).

    Modify the class to enable input and output of complex numbers via overloaded = and * operators, respectively (assignment and multiplication).

    Modify the class to enable input and output of complex numbers via overloaded >> and << operators, respectively (you should remove the print function from the class). Use friend functions to accomplish this.

    Overload the == and != operators to allow comparisons of complex numbers.

    Add friend member functions to enable input and output of complex numbers via overloaded >> and << operators, respectively (you should remove the print function from the class).
*/

class Complex{
   private:
      double realPart;
      double imaginaryPart;
   public:
      
      // Pre-Condition : two doubles to represent complex number
      // Post-Condition: complex number is created from doubles
      Complex(double real = 0, double imaginary = 0)
      {
         realPart = real;
         imaginaryPart = imaginary;
      }
      
      // getters
      double inline getRealPart() const { return realPart; };
      double inline getImaginaryPart() const { return imaginaryPart; };

		//overloaded assignment function definitions
		Complex operator+(const Complex &right) 
		{
			return Complex(realPart + right.getRealPart(), imaginaryPart + right.getImaginaryPart());
		}

		Complex operator-(const Complex &right)
		{
			return Complex(realPart - right.getRealPart(), imaginaryPart - right.getImaginaryPart());
		}
		
		Complex operator*(const Complex &right)
		{
			double real = realPart * right.getRealPart() + imaginaryPart * right.getImaginaryPart() * -1;
         double imaginary = realPart * right.getImaginaryPart() + imaginaryPart * right.getRealPart();
         return Complex(real, imaginary);
		}

		bool operator==(const Complex &right)
		{
			if(realPart == right.getRealPart() && imaginaryPart == right.getImaginaryPart())
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Complex &right)
		{
			if(realPart != right.getRealPart() && imaginaryPart != right.getImaginaryPart())
			{
				return true;
			}
			return false;
		}
		
		void operator=(const Complex &right)
		{
			realPart = right.getRealPart();
			imaginaryPart = right.getImaginaryPart();
		}
		
		friend std::ostream &operator<<(std::ostream &out, const Complex &source)
		{
			out << "(" << source.realPart << " + " << source.imaginaryPart << "i)\n";
		}
		
		friend std::istream &operator>>(std::istream &in, Complex &source)
		{
			in.ignore();
			in >> source.realPart;
			in.ignore();
			in >> source.imaginaryPart;
		}




      // Pre-Condition : N/A
      // Post-Condition: returns complex as a string
      std::string toString()
      {
         std::ostringstream ostr;
         ostr << "(" << realPart << " + " << imaginaryPart << "i)";
         return ostr.str();
      }

      // Pre-Condition : doubles to set as a complex number
      // Post-Condition: a complex number is formed with given doubles
      void setComplexNumber(double real, double imaginary)
      {
         realPart = real;
         imaginaryPart = imaginary;
      }
};


int main()
{
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
}
