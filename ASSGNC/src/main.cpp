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

class Complex{
   private:
      double realPart;
      double imaginaryPart;
   public:
      
      // Pre-Condition : two doubles to represent complex number
      // Post-Condition: complex number is created from doubles
      Complex(double real, double imaginary)
      {
         realPart = real;
         imaginaryPart = imaginary;
      }
      
      // getters
      double inline getRealPart() { return realPart; };
      double inline getImaginaryPart() { return imaginaryPart; };

      // Pre-Condition : a complex number
      // Post-Condition: creates and returns complex number with addition value
      Complex add(Complex c)
      {
         return Complex{realPart + c.getRealPart(), imaginaryPart + c.getImaginaryPart()};
      }

      // Pre-Condition : a complex number
      // Post-Condition: creates and returns complex number with subtraction value
      Complex subtract(Complex c)
      {
         return Complex{realPart - c.getRealPart(), imaginaryPart - c.getImaginaryPart()};
      }

      // Pre-Condition : a complex number
      // Post-Condition: creates and returns complex number with muliplication value
      Complex multiply(Complex c)
      {
         double real = realPart * c.getRealPart() + imaginaryPart * c.getImaginaryPart() * -1;
         double imaginary = realPart * c.getImaginaryPart() + imaginaryPart * c.getRealPart();
         return Complex{real, imaginary};
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
   for (double i = 1; i < 100; ++ i)
   {
     Complex a{i * 2, i + 2};
     Complex b{i * 3, i + 3};

     Complex c = a.add(b); // invoke add function and assign to object c
     std::cout << "Test case for Complex: add " << std::endl;
     std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << std::endl;

     a.setComplexNumber(i * 2, i + 2); // reset realPart and
     b.setComplexNumber(i * 3, i + 3); // and imaginaryPart

     std::cout << "Test case for Complex: subtract " << std::endl;
     c = a.subtract(b); // invoke subtract function and assign to object c
     std::cout << a.toString() << " - " << b.toString() << " = " << c.toString() << std::endl;
     std::cout << std::endl;

     a.setComplexNumber(i * 2, i + 2); // reset realPart and
     b.setComplexNumber(i * 3, i + 3); // and imaginaryPart

     std::cout << "Test case for Complex: multiply " << std::endl;
     c = a.multiply(b); // invoke multiply function and assign to object c
     std::cout << a.toString() << " * " << b.toString() << " = " << c.toString() << std::endl;
     std::cout << std::endl;
   }

}
