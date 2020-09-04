#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
	private:
		double real;  // real part
		double imag;  // imaginary part
		Complex getSelf () const;

		static double intPow (double x, int n = 2);  // Optimized for integer powers only, 2 by default
		static Complex realProduct (const Complex z, const double k = -1);
	public:
		Complex ();  // Defaults to 0 (0+0i) to prevent undefined errors.
		Complex (double real, double imag = 0);
		void setValue (double real, double imag);
		void setReal (double real);
		void setImag (double imag);
		double re () const;  // get real part
		double im () const;  // get imaginary part
		Complex conj () const;  // returns conjugate
		double norm () const;  // returns norm value

		bool equals (const Complex& z) const;
		Complex& add (const Complex& z);
		static Complex sum (const Complex z1, const Complex z2);
		Complex& subtract (const Complex& z);
		static Complex difference (const Complex z1, const Complex z2);  // returns z1 - z2
		Complex& multiply (const Complex& z);
		static Complex product (const Complex z1, const Complex z2);
		Complex& divide (const Complex& z);
		static Complex quotient (const Complex z1, const Complex z2);
		Complex reciprocal () const;

		// Operator Overloading
		Complex& operator = (const Complex& z) { setValue (z.re(), z.im()); return *this; }
		bool operator == (const Complex& z) const { return equals(z); }
		bool operator != (const Complex& z) const { return !equals(z); }
		Complex operator + (const Complex& z) const { return sum(getSelf(), z); }
		Complex operator - (const Complex& z) const { return difference(getSelf(), z); }
		Complex operator * (const Complex& z) const { return product(getSelf(), z); }
		Complex operator * (const double k) const { return realProduct(getSelf(), k); }  // real
		Complex operator / (const Complex& z) const { return quotient(getSelf(), z); }
		Complex operator / (const double k) const { return quotient(getSelf(), 1/k); }  // real
		Complex& operator += (const Complex& z) { return add(z); }
		Complex& operator -= (const Complex& z) { return subtract(z); }
		Complex& operator *= (const Complex& z) { return multiply(z); }
		Complex& operator *= (const double k) { setValue(k * real, k * imag); return *this; }
		Complex& operator /= (const Complex& z) { return divide(z); }
		Complex& operator /= (const double k) { setValue(real / k, imag / k); return *this; }
		Complex operator - () { return Complex(-real, -imag); }
		Complex operator ~ () { return conj(); }

		static const Complex i;
};

#endif