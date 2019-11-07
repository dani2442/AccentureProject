#pragma once
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include "Constants.h"
#include "Data.h"
class Decompose2
{
public:
	Decompose2();

	static std::vector<int> p;
	static bool isPrimes;
	static void Init() {
		if (isPrimes)return;
		isPrimes = true;
		p.push_back(1);
		for (int i = 2; i < NUM_PRIMES; i++) {
			bool prime = true;
			for (int j = sqrt((double)i); j > 1; j--) {
				if (i % j == 0) {
					prime = false;
					break;
				}
			}
			if (prime)p.push_back(i);
		}
		for (int i = 0; i < PRIMES; i++) {
			numeros[i].resize(MAX);
		}
		
	}

	void decomp(long long n, int noPrime);
	void _Operations(int count,long long n,std::string& s);


	static void read1();
	static void read2();

	int noPrime;

	int min;
	std::string minS;

	void Reset() { minS = ""; min = 9999; }
private:


	static std::vector<Data4> combins[PRIMES][DEPTH];
	static std::vector<Data> numeros[PRIMES];

	static std::string itos(int i) {
		std::stringstream s;
		s << i;
		return s.str();
	}
};
