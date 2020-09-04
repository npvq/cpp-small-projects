#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>

class Polynomial
{
	private:
		std::vector<double> coefficients;
		int degree;
		
		static int factorialBetween (int b, int a = 0);  // Special Factorial b!/a!
		static std::vector<double> arrayToVec(double* arr);  // For converting double* to std::vector<double>
		static std::vector<double> truncateVec(std::vector<double> vec);  // Truncate leading zeros (for optimizaiton and comparison)

		static std::vector<double> multiplyScalarVec (std::vector<double> vec, double scalar = -1);  // defaults to -1 (acts as flip())
		static std::vector<double> addVec (std::vector<double> vec1, std::vector<double> vec2);  // Adds vectors in the "coefficient" style
		static std::vector<double> subtractVec (std::vector<double> vec1, std::vector<double> vec2);  // Subtracts vectors in the "coefficient" style: vec1 - vec2.
		//static std::vector<double> productVec (std::vector<double> vec1, std::vector<double> vec2);  // Multiplies vectors in the "coefficient" style

		static const std::vector<double> nullVec;  // The standard (smallest) null/emtpy vector
		static const Polynomial nullPoly;  // The standard (smallest) null/empty polynomial. Note: Nullpoly also has degree 0.
		static const std::vector<double> unitVec;
		static const Polynomial unitPoly;  // Unit polynomial has degree 0 and is a multiplicative identity.

	public:
		Polynomial ();  // No specification result in a unit polynomial (to prevent undefined errors)
		Polynomial (const double* coef);
		Polynomial (std::vector<double> coef);
		~Polynomial ();
		void setCoefficients (const double* coef);
		void setCoefficients (std::vector<double> coef);
		std::vector<double> getCoefficients () const;
		int getDegree () const;

		// Operations
		bool equals (const Polynomial& poly) const;
		Polynomial& add (const Polynomial& poly);
		Polynomial& subtract (const Polynomial& poly);
		Polynomial& multiply (const Polynomial& poly);
		Polynomial& scalarMultiply (const double k);

		bool isNull () const { return coefficients == nullVec; }  // In case this is useful

		// Operators
		Polynomial& operator = ( const Polynomial& poly ) { setCoefficients(poly.getCoefficients()); return *this; }  // Assignment (=)
		bool operator == ( const Polynomial& poly ) const { return equals(poly); }  // Binary Comparison (==)
		bool operator != ( const Polynomial& poly ) const { return !equals(poly); }  // Binary Comparison (!=)
		Polynomial operator + ( const Polynomial& poly ) const { return Polynomial(addVec(coefficients, poly.getCoefficients())); }  // Binary (+)
		Polynomial operator - ( const Polynomial& poly ) const { return Polynomial(subtractVec(coefficients, poly.getCoefficients())); }  // Binary (-)
		Polynomial operator * ( const Polynomial& poly ) const { return Polynomial(productVec(coefficients, poly.getCoefficients())); }  // Binary (*)
		Polynomial operator * ( const double k ) const { return Polynomial(multiplyScalarVec(coefficients, k)); }  // Binary (*) Scalar
		Polynomial& operator += ( const Polynomial& poly ) { return add(poly); }  // Assignment (+=)
		Polynomial& operator -= ( const Polynomial& poly ) { return subtract(poly); }  // Assignment (-=)
		Polynomial& operator *= ( const Polynomial& poly ) { return multiply(poly); }  // Assignment (*=)
		Polynomial& operator *= ( const double k ) { return scalarMultiply(k); }  // Assignment (*=)

		// Calculations
		double evaluate (double x);
		double derivativeEval (double x, int der = 1);
		double integralEval (double a, double b, int inte = 1);  // S(a, b)
		Polynomial derivativePoly (int der = 1);
		Polynomial integralPoly (int inte = 1);  // In the most basic (using 0s) +C form
		double antiderivativeEval (double a, double b);  // Faster method of eval(b) - eval(a) for calculating area under derivative.

		// Applications
		static double newtonApprox(Polynomial poly, double g = 0, int max = 10);  // g is the initial guess. max is max tries
		static long double newtonApproxL(Polynomial poly, long double g = 0, int max = 10);  // for more precision

		static std::vector<double> productVec (std::vector<double> vec1, std::vector<double> vec2);
};

#endif