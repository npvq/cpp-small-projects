#include <cmath>

#include "Complex.h"

using namespace std;

const Complex Complex::i(0, 1);

Complex::Complex ()
{
	Complex::real = 0;
	Complex::imag = 0;
}

Complex::Complex (double real, double imag)
{
	Complex::real = real;
	Complex::imag = imag;
}

void Complex::setValue (double real, double imag)
{
	Complex::real = real;
	Complex::imag = imag;
}

void Complex::setReal (double real)
{
	Complex::real = real;
}

void Complex::setImag (double imag)
{
	Complex::imag = imag;
}

double Complex::re () const
{
	return Complex::real;
}

double Complex::im () const
{
	return Complex::imag;
}

Complex Complex::conj () const
{
	return Complex(Complex::real, -(Complex::imag));
}

double Complex::norm () const
{
	return sqrt ( (Complex::real * Complex::real) + (Complex::imag * Complex::imag) );
}

// Operations

bool Complex::equals (const Complex& z) const
{
	return Complex::real == z.re() && Complex::imag == z.im();
}

Complex& Complex::add (const Complex& z)
{
	Complex::setValue(Complex::real + z.re(), Complex::imag + z.im());
	return *this;
}

Complex Complex::sum (const Complex z1, const Complex z2)
{
	return Complex (z1.re() + z2.re(), z1.im() + z2.im());
}

Complex& Complex::subtract (const Complex& z)
{
	Complex::setValue(Complex::real - z.re(), Complex::imag - z.im());
	return *this;
}

Complex Complex::difference (const Complex z1, const Complex z2)
{
	return Complex (z1.re() - z2.re(), z1.im() - z2.im());
}

Complex& Complex::multiply (const Complex& z)
{
	Complex::setValue( (Complex::real * z.re()) - (Complex::imag * z.im()), (Complex::real * z.im()) + (Complex::imag * z.re()) );
	return *this;
}

Complex Complex::product (const Complex z1, const Complex z2)
{
	return Complex ( (z1.re() * z2.re()) - (z1.im() * z2.im()), (z1.re() * z2.im()) + (z1.im() * z2.re()) );
}

Complex& Complex::divide (const Complex& z)
{
	return Complex::multiply(z.reciprocal());
}

Complex Complex::quotient (const Complex z1, const Complex z2)
{
	return Complex::product(z1, z2.reciprocal());
}

Complex Complex::reciprocal () const
{
	return Complex::realProduct(Complex::conj(), 1 / Complex::norm());
}

// Supplementary methods

double Complex::intPow (double x, int n) //(Private) Optimized, should be a bit faster than std::pow(double, int)
{
	if (n <= 0) return (n == 0) ? 1 : (1 / Complex::intPow(x, n));
	double y = x;
	for (int i = n-1; i--;) {
		y *= x;
	}
	return y;
}

Complex Complex::realProduct (const Complex z, const double k)
{
	return Complex (k * z.re(), k * z.im());
}

Complex Complex::getSelf () const
{
	return Complex (Complex::real, Complex::imag);
}
