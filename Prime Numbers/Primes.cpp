#include <cmath>  // Mathematical Operations
#include <cstdlib>  // func: std::abs()
#include <limits>  // numeric_limits<int>::max() etc
#include <list>  // Type: std::list - std::list<int>
#include <random>  // func: std::uniform_int_distribution, std::random_device, std::mt19937
#include <string>  // Type: std::string
#include <utility>  // func: std::swap()

#include "Primes.h"

using namespace std;

const list<int> Primes::lowPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
	41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
	211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
	307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
	499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
	709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821,
	823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929,
	937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

const int Primes::lowPrimesNext = 1009;  

bool Primes::isPrime (const long n)
{
	// Must use a strictly positive number
	assert (n > 0);

	// Define 1 to not be a prime
	if (n == 1) {
		return false;
	}
	int cmax = int (sqrt(n));  // Maximum considered factor, int rounds down and computes comparisons faster
	for (long i = 2; i <= cmax; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

bool Primes::isPrimeEfficient (const long n)
{
	// Must use a strictly positive number
	assert (n > 0);

	// Define 1 to not be a prime
	if (n == 1) {
		return false;
	}
	if (! Primes::fermatTest (n, 10)) {
		return false;
	}
	int cmax = int (sqrt(n));  // Maximum considered factor, int rounds down and computes comparisons faster
	for (list<int>::const_iterator i = Primes::lowPrimes.begin(); i != Primes::lowPrimes.end(); ++i) {
		if (*i > cmax) {
			return true;
		} else if (n % *i == 0) {
			return false;
		}
	}
	if (! Primes::millerRabinTest (n, 10)) {
		return false;
	}
	// First prime after 997 is 1009
	if (cmax >= Primes::lowPrimesNext) {
		for (long i = Primes::lowPrimesNext; i <= cmax; ++i) {
			if (n % i == 0) {
				return false;
			}
		}
	}
	return true;
}

int Primes::pi (const long n)
{
	if (n < 2) {
		return 0;
	} else if (n == 2) {
		return 1;
	}

	list<long> primes;
	primes.push_back(2);
	for (long p = 3; p <= n; ++p) {
		bool current_prime = true;
		for (list<long>::iterator i = primes.begin(); i != primes.end(); ++i) {
			if ((*i)*(*i) > p) {
				break;
			} else if (p % *i == 0) {
				current_prime = false;
				break;
			}
		}
		if (current_prime) {
			primes.push_back(p);
		}
	}
	return primes.size();
}

int Primes::piEfficient (const long n)
{
	if (n < 2) {
		return 0;
	}

	list<long> primes;
	for (list<int>::const_iterator i = Primes::lowPrimes.begin(); i != Primes::lowPrimes.end(); ++i) {
		if (*i > n) {
			break;
		}
		primes.push_back(*i);
	}
	for (long p = Primes::lowPrimesNext; p <= n; ++p) {
		bool current_prime = true;
		for (list<long>::iterator i = primes.begin(); i != primes.end(); ++i) {
			if ((*i)*(*i) > p) {
				break;
			} else if (p % *i == 0) {
				current_prime = false;
				break;
			}
		}
		if (current_prime) {
			primes.push_back(p);
		}
	}
	return primes.size();
}

list<long> Primes::primeFactorize (long n)
{
	// Must use a strictly positive number
	assert (n > 0);

	list<long> factors;
	int counter;

	for (list<int>::const_iterator i = Primes::lowPrimes.begin(); i != Primes::lowPrimes.end(); ++i) {
		counter = 0;
		while (n % *i == 0) {
			n /= *i;
			counter += 1;
		}
		if (counter > 0) {
			factors.push_back(*i);
		}
		if (n == 1) {
			break;
		}
	}
	for (int i = Primes::lowPrimesNext; n != 1; ++i) {
		counter = 0;
		while (n % i == 0) {
			n /= i;
			counter += 1;
		}
		if (counter != 0) {
			factors.push_back(i);
		}
	}
	return factors;
}

string Primes::primeDecompose (long n)
{
	// See Java File for Original Method/Function
	// Must use a strictly positive number
	assert (n > 0);

	string outstr;
	int counter;

	for (list<int>::const_iterator i = Primes::lowPrimes.begin(); i != Primes::lowPrimes.end(); ++i) {
		counter = 0;
		while (n % *i == 0) {
			n /= *i;
			counter += 1;
		}
		if (counter == 1) {
			outstr += to_string(*i).append(" ");
		} else if (counter > 1) {
			outstr += to_string(*i).append("^").append(to_string(counter)).append(" ");
		}
		if (n == 1) {
			break;
		}
	}
	for (int i = Primes::lowPrimesNext; n != 1; ++i) {
		counter = 0;
		while (n % i == 0) {
			n /= i;
			counter += 1;
		}
		if (counter == 1) {
			outstr += to_string(i).append(" ");
		} else if (counter > 1) {
			outstr += to_string(i).append("^").append(to_string(counter)).append(" ");
		}
	}
	if (!outstr.empty()) {
		//outstr.erase (1, 1);
		return outstr.substr(0, outstr.size()-1);
		//return outstr;
	} else {
		return "ERROR";
	}
	return outstr;
}

// Primality Tests and Related Important Private Methods
int Primes::jakobiSymbol (int a, int n)
{
	int j = 1;
	while (a != 0) {
		while (a % 2 == 0) {
			a = a/2;
			int nmod = n % 8;
			if (nmod == 3 || nmod == 5) {
				j = -j;
			}
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3) {
			j = -j;
		}
		a = a % n;
	}
	return n==1 ? j : 0;
}

int Primes::jakobiSymbolL (long a, long n)  // In case the number is too big
{
	int j = 1;
	while (a != 0) {
		while (a % 2 == 0) {
			a = a/2;
			int nmod = n % 8;
			if (nmod == 3 || nmod == 5) {
				j = -j;
			}
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3) {
			j = -j;
		}
		a = a % n;
	}
	return n==1 ? j : 0;
}

/* This program can't be used. We can't take a to the power of n, n is too big
bool Primes::solovayStrassenTest (long n)
{
	// Must use a strictly odd positive number greater than 3 (primality test)
	assert (n > 3 && n % 2 == 1);
	default_random_engine generator;
	uniform_int_distribution<long>  distr(2, n-1);
	long a = distr(generator);

	// The following types can be optimized (to int) but it may not be worth the computation
	long x = long (pow(a, (n-1)/2)) % n;  // Note: n-1 is even
	int j = jakobiSymbolL(a, n);

	return (j == 0 || x != j) ? false : true;
	// true = Might be a prime (less than 50% composite pass this test)
	// false = Definitely not a prime
}
*/

int Primes::powermod (int a, int n, const int p)
{
	int m = 1;  // Result
	a %= p;

	while (n > 0) {
		if (n % 2 == 1) {
			m = (m*a) % p;
		}

		// n must be even now
		n = n >> 1;
		a = (a * a) % p;
	}

	return m;
}

long Primes::powermodL (long a, long n, const long p)
{
	long m = 1;  // Result
	a %= p;

	while (n > 0) {
		if (n % 2 == 1) {
			m = (m*a) % p;
		}

		// n must be even now
		n = n >> 1;
		a = (a * a) % p;
	}

	return m;
}

int Primes::gcd (const int a, const int b)
{
	if (a < b) {
		return gcd(b, a);
	} else if (a % b == 0) {
		return b;
	} else {
		return gcd(b, a % b);
	}
}

long Primes::gcdL (const long a, const long b)
{
	if (a < b) {
		return gcdL(b, a);
	} else if (a % b == 0) {
		return b;
	} else {
		return gcdL(b, a % b);
	}
}

bool Primes::fermatTest (const long n, const int k)  // Tries k times
{
	assert (n > 0);  // strictly positive number

	// Trivial Cases
	if (n < 4) return n == 2 || n == 3;  // It is still asserted that n>0 for error catching.

	//uniformly random generator
	default_random_engine generator;
	uniform_int_distribution<long>  distr(2, n-2);

	for (int i = 0; i < k; ++i) {
		long a = distr(generator);

		// Check for coprime
		if (gcdL(n, a) != 1) return false;

		// Fermat's little theorem
		if (powermodL(a, n-1, n) != 1) return false;
	}
	return true;
	// true = Might be a prime, accuracy depends on k
	// false = Definitely not a prime
}

bool Primes::millerRabinTest (const long n, const int k)  // Tries k times
{
	assert (n > 0);  // strictly positive number

	// Trivial Cases
	if (n < 4) return n == 2 || n == 3;  // It is still asserted that n>0 for error catching.

	long d = n - 1;
	while (d % 2 == 0) {
		d /= 2;
	}

	//uniformly random generator
	default_random_engine generator;
	uniform_int_distribution<long>  distr(2, n-2);

	for (int i = 0; i < k; ++i) {
		long a = distr(generator);
		long x = powermodL(a, d, n);
		bool notFlip;

		// Miller Rabin Test
		if (x != 1 && x != n - 1) {
			// Keep squaring x while one of the following doesn't 
			// happen 
			// (i)   d does not reach n-1 
			// (ii)  (x^2) % n is not 1 
			// (iii) (x^2) % n is not n-1 
			notFlip = true;  // condition (iii) has not been satisfied
			while (d != n - 1) {
				x = (x * x) % n;
				d *= 2;

				if (x == 1) {
					return false;
				} else if (n == n - 1) {
					notFlip = false;
					break;
				}
			}
			if (notFlip) return false;
		}
	}

	// Miller Rabin tests passed
	return true;
}
