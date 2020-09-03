#include <cmath>  // Mathematical Operations
#include <list>  // Type: std::list - std::vector<double>

#include "Polynomial.h"
#include <iostream>

using namespace std;

const vector<double> Polynomial::nullVec = {0};
const Polynomial Polynomial::nullPoly(nullVec);

Polynomial::Polynomial (const double* coef)
{
	vector<double> temp(coef, coef+sizeof(coef));
	temp = Polynomial::truncateVec(temp);
	Polynomial::coefficients = temp;
	Polynomial:degree = temp.size() - 1;
}

Polynomial::Polynomial (vector<double> coef)
{
	coef = Polynomial::truncateVec(coef);
	Polynomial::coefficients = coef;
	Polynomial::degree = coef.size() - 1;
}

Polynomial::~Polynomial ()
{
	Polynomial::coefficients.clear();
}

void Polynomial::setCoefficients (const double* coef)
{
	vector<double> temp(coef, coef+sizeof(coef));
	temp = Polynomial::truncateVec(temp);
	Polynomial::coefficients = temp;
	Polynomial:degree = temp.size() - 1;
}

void Polynomial::setCoefficients (vector<double> coef)
{
	coef = Polynomial::truncateVec(coef);
	Polynomial::coefficients = coef;
	Polynomial::degree = coef.size() - 1;
}

vector<double> Polynomial::getCoefficients () const
{
	return Polynomial::coefficients;
}

int Polynomial::getDegree () const
{
	return Polynomial::degree;
}

vector<double> Polynomial::arrayToVec (double* arr)  // Static, Private method for converting double* to std::vector<double>
{
	vector<double> tempVec (arr, arr+sizeof(arr));
	return tempVec;
}

vector<double> Polynomial::truncateVec (vector<double> vec)  // Truncate leading zeros (for optimizaiton and comparison)
{
	vector<double>::iterator iter = vec.begin();
	while (*iter == 0 && iter != vec.end()-1) {iter ++;}
	vector<double> newVec(iter, vec.end());

	return newVec;
}

vector<double> Polynomial::addVec (vector<double> vec1, vector<double> vec2)  // Adds vectors in the "coefficient" style
{
	// if (vec2 == Polynomial::nullVec) return vec1;  // Filter out null vectors (not sure if necessary)
	if (vec1.size() < vec2.size()) return Polynomial::addVec (vec2, vec1);

	vector<double>::reverse_iterator riter = vec1.rbegin();
	for (vector<double>::reverse_iterator i = vec2.rbegin(); i != vec2.rend(); ++i) {
		*riter += *i;
		riter++;
	}
	return vec1;
}

vector<double> Polynomial::multiplyScalarVec (vector<double> vec, double scalar)  // defaults to -1 (acts as flip())
{
	if (!scalar) return Polynomial::nullVec;  // Case: scalar == 0
	for (vector<double>::iterator i = vec.begin(); i != vec.end(); ++i) {
		*i *= scalar;
	}
	return vec;
}

vector<double> Polynomial::subtractVec (vector<double> vec1, vector<double> vec2)  // Subtracts vectors in the "coefficient" style: vec1 - vec2.
{
	return Polynomial::addVec(vec1, Polynomial::multiplyScalarVec(vec2));
}

vector<double> Polynomial::productVec (vector<double> vec1, vector<double> vec2)  // Multiplies vectors in the "coefficient" style
{
	if (vec1.size() > vec2.size()) return Polynomial::productVec(vec2, vec1);
	vector<double> product = Polynomial::nullVec;
	vector<double>::iterator iter;
	for (iter = vec1.begin(); iter != vec1.end()-1; ++iter) {
		product = Polynomial::addVec(Polynomial::multiplyScalarVec(vec2, *iter), product);
		product.push_back(0);
	}
 	product = Polynomial::addVec(Polynomial::multiplyScalarVec(vec2, *iter), product);
 	return product;
}

bool Polynomial::equals (const Polynomial& poly) const
{
	return Polynomial::coefficients == poly.getCoefficients();
}

Polynomial& Polynomial::add (const Polynomial& poly)
{
	setCoefficients(addVec(coefficients, poly.getCoefficients()));
	return *this;
}

Polynomial& Polynomial::subtract (const Polynomial& poly)
{
	setCoefficients(subtractVec(coefficients, poly.getCoefficients()));
	return *this;
}

Polynomial& Polynomial::multiply (const Polynomial& poly)
{
	setCoefficients(productVec(coefficients, poly.getCoefficients()));
	return *this;
}

// Calculation Methods

double Polynomial::intPow (double x, int n) //(Private) Optimized, should be a bit faster than std::pow(double, int)
{
	assert (n >= 0);  // prevent negative powers
	if (n == 0) return 1;
	double y = x;
	for (int i = n-1; i--;){
		y *= x;
	}
	return y;
}

int Polynomial::factorialBetween (int b, int a)  // Special Factorial, (a, b]: (n, 0) yields n!, (b, a) yields b!/a!
{
	if (a >= b) return (a == b) ? 1 : 0;

	int n = 1;
	for (int i = b; i > a; i--) {
		n *= i;
	}
	return n;
}

double Polynomial::evaluate (double x)
{
	double y = 0;
	int pow = 0;
	for (vector<double>::reverse_iterator i = Polynomial::coefficients.rbegin(); i != Polynomial::coefficients.rend(); ++i) {
		y += Polynomial::intPow(x, pow) * (*i);
		pow++;
	}
	return y;
}
/* Alternatively: This is the same as above but slower. It works similar to the derivative method, for reference.
double Polynomial::evaluate (double x)
{
	double y = 0;
	int pow = Polynomial::degree;
	for (vector<double>::iterator i = Polynomial::coefficients.begin(); i != Polynomial::coefficients.end(); ++i) {
		y += Polynomial::intPow(x, pow) * (*i);
		pow--;
	}
	return y;
}
*/

double Polynomial::derivativeEval (double x, int der)
{
	assert (der > 0);  // Derivation must be a strictly positive integer
	double y = 0;
	int pow = Polynomial::degree;
	if (der > pow) return 0;
	for (vector<double>::iterator i = Polynomial::coefficients.begin(); i != Polynomial::coefficients.end() && pow >= der; ++i) {
		y += (*i) * Polynomial::factorialBetween(pow, pow-der) * intPow(x, pow-der);
		pow--;
	}
	return y;
}

Polynomial Polynomial::derivativePoly (int der)
{
	assert (der > 0);  // Derivation must be a strictly positive integer
	int pow = Polynomial::degree;
	if (der > pow) return Polynomial::nullPoly;
	vector<double> coef;
	for (vector<double>::iterator i = Polynomial::coefficients.begin(); i != Polynomial::coefficients.end() && pow >= der; ++i) {
		coef.push_back((*i) * Polynomial::factorialBetween(pow, pow-der));
		pow--;
	}
	return Polynomial(coef);
}

double Polynomial::integralEval(double a, double b, int inte)
{
	assert (inte > 0);  // Integration must be a strictly positive integer
	double y = 0;
	int pow = 0;
	for (vector<double>::reverse_iterator i = Polynomial::coefficients.rbegin(); i != Polynomial::coefficients.rend(); ++i) {
		y += (Polynomial::intPow(b, pow+inte) - Polynomial::intPow(a, pow+inte)) / Polynomial::factorialBetween(pow+inte, pow) * (*i);
		pow++;
	}
	return y;
}

Polynomial Polynomial::integralPoly(int inte)  // Returns the most basic integral, new terms have coefficient zero
{
	assert (inte > 0);  // Integration must be a strictly positive integer
	int pow = Polynomial::degree;
	vector<double> coef;
	for (vector<double>::iterator i = Polynomial::coefficients.begin(); i != Polynomial::coefficients.end(); ++i) {
		coef.push_back((*i) / Polynomial::factorialBetween(pow+inte, pow));
		pow--;
	}
	for (int i = inte; i--;) coef.push_back(0);
	return Polynomial(coef);
}

double Polynomial::antiderivativeEval (double a, double b)
{
	double y = 0;
	int pow = 0;
	for (vector<double>::reverse_iterator i = Polynomial::coefficients.rbegin(); i != Polynomial::coefficients.rend(); ++i) {
		y += (Polynomial::intPow(b, pow) - Polynomial::intPow(a, pow)) * (*i);
		pow++;
	}
	return y;
}

// More Applied Calculation Methods

double Polynomial::newtonApprox (Polynomial poly, double g, int max)  // Simple newtons approximation: g is the initial guess. max is max tries
{
	Polynomial derPoly = poly.derivativePoly();
	double g1;  // To stop the function and prevent wasting computation after a certain accuracy threshold has been reached
	for (int i = max; i--;) {
		g1 = g;
		g = g - (poly.evaluate(g) / derPoly.evaluate(g));
		if (abs(g-g1) < 0.00000000000001) break;
	}
	return g;
}

long double Polynomial::newtonApproxL (Polynomial poly, long double g, int max)  // Simple newtons approximation: g is the initial guess. max is max tries
{
	Polynomial derPoly = poly.derivativePoly();
	long double g1;  // To stop the function and prevent wasting computation after a certain accuracy threshold has been reached
	for (int i = max; i--;) {
		g1 = g;
		g = g - (poly.evaluate(g) / derPoly.evaluate(g));
		if (abs(g-g1) < 0.00000000000000000000000000000001L) break;
	}
	return g;
}
