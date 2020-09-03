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
	Polynomial x({1, 3, 3, 1});
	printVec(x.getCoefficients());

	Polynomial y({0, 0});

	cout << "xnull " << x.isNull() << ", ynull " << y.isNull() << endl;

	printVec(Polynomial::productVec(x.getCoefficients(), y.getCoefficients()));

	printVec((x - y).getCoefficients());

	return 0;
}
