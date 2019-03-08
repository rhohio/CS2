#include "Complex.hpp"

//Pre-Condition : N/A
//Post-Condition: Creates a Complex object given real and imaginary,
//				  Assigns values to zero if given nothing
Complex::Complex(double real = 0, double imaginary = 0)
{
	realPart = real;
	imaginaryPart = imaginary;
}

Complex::Complex()
{
	realPart, imaginaryPart = 0;
}

//Pre-Condition : given a double
//Post-Condition: sets realPart of Complex object to doulbe given
void Complex::setRealPart(double real)
{
	realPart = real;
}

//Pre-Condition : given a double
//Post-Condition: sets imaginaryPart of Complex object to doulbe given
void Complex::setImaginaryPart(double imaginary)
{
	imaginaryPart = imaginary;
}

//Pre-Condition : given a Complex Object
//Post-Condition: returns addition of two Complex numbers as an object
Complex Complex::operator+(const Complex &right) 
{
	return Complex(realPart + right.getRealPart(), imaginaryPart + right.getImaginaryPart()); 
}

//Pre-Condition : given a Complex Object
//Post-Condition: returns subtraciton of two Complex numbers as an object
Complex Complex::operator-(const Complex &right) 
{
	return Complex(realPart - right.getRealPart(), imaginaryPart - right.getImaginaryPart()); 
}

//Pre-Condition : given a Complex Object
//Post-Condition: returns multiplication of two Complex numbers as an object
Complex Complex::operator*(const Complex &right)
{
	double real = realPart * right.getRealPart() + imaginaryPart * right.getImaginaryPart() * -1;
	double imaginary = realPart * right.getImaginaryPart() + imaginaryPart * right.getRealPart();
	return Complex(real, imaginary);
}

//Pre-Condition : given a Complex object
//Post-Condition: returns true if two complex objects equal each other
bool Complex::operator==(const Complex &right)
{
	return ((realPart == right.getRealPart()) && (imaginaryPart == right.getImaginaryPart()));
}

//Pre-Condition : given a complex object
//Post-Condition: returns true if two complex objects don't equal each other
bool Complex::operator!=(const Complex &right)
{
	return !((realPart == right.getRealPart()) && (imaginaryPart == right.getImaginaryPart()));
}

//Pre-Condition : given a complex object
//Post-Condition: assigns all values of right complex object to the left complex object
void Complex::operator=(const Complex &right)
{
	realPart 	  = right.getRealPart();
	imaginaryPart = right.getImaginaryPart();
}

//Pre-Condition : given an out stream, and a complex object
//Post-Condition: outputs to out stream the complex number in the form (a + bi)
std::ostream &operator<<(std::ostream &out, const Complex &source)
{
	out << "(" << source.realPart << " + " << source.imaginaryPart << "i)\n";
}

//Pre-Condition : given an input stream and a complex object
//Post-Condition: inputs real and imagniary part into the complex object
std::istream &operator>>(std::istream &in, Complex &source)
{
	in.ignore();
	in >> source.realPart;
	in.ignore();
	in >> source.imaginaryPart;
}