#ifndef COMPLEX_H // include guard
#define COMPLEX_H

#include <iostream>

class Complex{
	private:
      double realPart;
      double imaginaryPart;
   public:
		Complex(double, double);
      
      // setters/getters
      double inline getRealPart() const { return realPart; };
      double inline getImaginaryPart() const { return imaginaryPart; };
      void setComplexNumber(double, double);

		//overloaded assignment function definitions
		Complex operator+(const Complex&);
		Complex operator-(const Complex&);
		Complex operator*(const Complex&);
		bool 	  operator==(const Complex&);
		bool 	  operator!=(const Complex&);
		void    operator=(const Complex &right);
		friend std::ostream &operator<<(std::ostream&, const Complex&);
		friend std::istream &operator>>(std::istream&, Complex&);
};

#endif