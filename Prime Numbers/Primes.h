#ifndef PRIMES_H
#define PRIMES_H

#include <list>
#include <string>

class Primes  // [Static] Namespace Class (No Instantiation)
{
	private:
		static const std::list<int> lowPrimes;  // Some small primes below 10^3
		static const int lowPrimesNext; // Smallest prime after the array
		// Primality Tests
		static int powermod (int a, int n, const int p);  // calculates (a^n) % p in O(log y)
		static long powermodL (long a, long n, const long p);  // For large numbers
		static int gcd(const int a, const int b);  // Recursive
		static long gcdL(const long a, const long b);  // For large numbers
		static int jakobiSymbol (int a, int n);
		static int jakobiSymbolL (long a, long n);  // For large numbers
		static bool fermatTest (const long n, const int k = 5);  // k tries
		static bool millerRabinTest (const long n, const int k = 5);
		//static bool solovayStrassenTest (long n);  // Can't be used
	public:
		static bool isPrime (const long n);
		static bool isPrimeEfficient (const long n);
		static int pi (const long n);
		static int piEfficient (const long n);
		static std::list<long> primeFactorize(long n);  // Passes back a list object
		static std::string primeDecompose(long n);  // Check java file for original function

		//temporary access
		static int jakobi (int a, int n) {return jakobiSymbol(a, n);}
		static bool fermat (long n, int k) {return fermatTest(n, k);}
		static bool miller (long n, int k) {return millerRabinTest(n, k);}
};

#endif
