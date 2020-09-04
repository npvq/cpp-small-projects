#include <iostream>
#include <string>
#include <iomanip>
#include "Polynomial.h"

using namespace std;

void printVec(vector<double> vec) {
	for (vector<double>::iterator i = vec.begin(); i != vec.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

int main () {
	// TODO: Write a good test file.

	Polynomial x({1, 0, 3});
	printVec(x.getCoefficients());

	Polynomial y({2, 1});

	Polynomial z = x * 3;
	x *= y;
	printVec(x.getCoefficients());
	printVec(y.getCoefficients());
	printVec(z.getCoefficients());

	cout << "xnull " << x.isNull() << ", ynull " << y.isNull() << endl;

	printVec(Polynomial::productVec(x.getCoefficients(), y.getCoefficients()));

	printVec((x - y).getCoefficients());

	return 0;
}
