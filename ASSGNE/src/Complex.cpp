#include "Complex.hpp"

Complex::Complex(double real = 0, double imaginary = 0)
{
	realPart = real;
	imaginaryPart = imaginary;
}

void Complex::setComplexNumber(double real, double imaginary)
{
	realPart = real;
	imaginaryPart = imaginary;
}

Complex Complex::operator+(const Complex &right) 
{
	return Complex(realPart + right.getRealPart(), imaginaryPart + right.getImaginaryPart()); 
}

Complex Complex::operator-(const Complex &right) 
{
	return Complex(realPart - right.getRealPart(), imaginaryPart - right.getImaginaryPart()); 
}

Complex Complex::operator*(const Complex &right)
{
	double real = realPart * right.getRealPart() + imaginaryPart * right.getImaginaryPart() * -1;
	double imaginary = realPart * right.getImaginaryPart() + imaginaryPart * right.getRealPart();
	return Complex(real, imaginary);
}

bool Complex::operator==(const Complex &right)
{
	return ((realPart == right.getRealPart()) && (imaginaryPart == right.getImaginaryPart()));
}

bool Complex::operator!=(const Complex &right)
{
	return !((realPart == right.getRealPart()) && (imaginaryPart == right.getImaginaryPart()));
}

void Complex::operator=(const Complex &right)
{
	realPart 	  = right.getRealPart();
	imaginaryPart = right.getImaginaryPart();
}

std::ostream &operator<<(std::ostream &out, const Complex &source)
{
	out << "(" << source.realPart << " + " << source.imaginaryPart << "i)\n";
}
		
std::istream &operator>>(std::istream &in, Complex &source)
{
	in.ignore();
	in >> source.realPart;
	in.ignore();
	in >> source.imaginaryPart;
}