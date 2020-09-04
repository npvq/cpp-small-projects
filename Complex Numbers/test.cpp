#include <iostream>

#include "Complex.h"

using namespace std;

int main ()
{
	Complex x(1, 1);
	x /= sqrt(2);
	x *= x;
	cout << x.re() << ", " << x.im() << endl;
	return 0;
}
