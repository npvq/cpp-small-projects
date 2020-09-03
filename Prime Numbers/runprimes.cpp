#include <iostream>
#include "Primes.h"
#include <list>

using namespace std;


const char *help = "Prime Calculator. Functions:\n"
	"  prime -- isPrime(long)\n"
	" primef -- isPrimeEfficient(long)\n"
	"     pi -- pi(long)\n"
	"    pif -- piEfficient(long)\n"
	" factor -- primeFactorize(long)\n"
	"decomps -- primeDecompose(long)";

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

int main(int argc, char** argv)
{
	if (argc <= 1) {  // ((argv[1] != NULL) && (argv[1][0] == '\0'))
		cout << "Invalid option, try \"help\" instead?" << endl;
		return 0;
	}
	if (!strcmp (argv[1], "help")) {
		cout << help << endl;
		return 0;
	}
	if (argc < 3) {
		cout << "ERROR Not enough arguments.\ntry \"help\" instead?" << endl;
		return 1;
	}
	switch (str2int(argv[1])) {
		case str2int("prime"): {
			cout << Primes::isPrime(stol (argv[2],nullptr,10)) << endl;
			break;
		}
		case str2int("primef"): {
			cout << Primes::isPrimeEfficient(stol (argv[2],nullptr,10)) << endl;
			break;
		}
		case str2int("pi"): {
			cout << Primes::pi(stol (argv[2],nullptr,10)) << endl;
			break;
		}
		case str2int("pif"): {
			cout << Primes::piEfficient(stol (argv[2],nullptr,10)) << endl;
			break;
		}
		case str2int("decomps"): {
			cout << Primes::primeDecompose(stol (argv[2],nullptr,10)) << endl;
			break;
		}
		case str2int("factor"): {
			const list<long> factors = Primes::primeFactorize(stol (argv[2],nullptr,10));
			for (list<long>::const_iterator i = factors.begin(); i != factors.end(); ++i) {
				cout << *i << " ";
			}
			cout << endl;
			break;
		}
		case str2int("fermat"): {
			cout << Primes::fermat(stol (argv[2],nullptr,10), stoi (argv[3],nullptr,10)) << endl;
			break;
		}
		case str2int("miller"): {
			cout << Primes::miller(stol (argv[2],nullptr,10), stoi (argv[3],nullptr,10)) << endl;
			break;
		}
		default: {
			cout << "ERROR: option not found" << endl;
			return 1;
		}
	}
	return 0;
}
