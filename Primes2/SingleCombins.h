#pragma once
#include "Constants.h"
#include "Data.h"
#include <fstream>
#include <vector>

class SingleConbins
{
public:
	SingleConbins();
	void Start(int noPrime);
	void exportData(std::string& s);

	bool isOK;

	static void calculatePrimes() {
		if (isPrimes)return;
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
		isPrimes = true;
	}
	static std::vector<int> p;
	static bool isPrimes;

	std::vector<Data3> combins[DEPTH];
private:
	int noPrime;
	std::vector<int> primes2;

	void calculateOperations();

	void check(Data3& n, std::vector<Data3>& vec);

	void _Operations(std::vector<Data3>&a,std::vector<Data3>&b,std::vector<Data3>&c);

	std::string itos(int i) {
		std::stringstream s;
		s << i;
		return s.str();
	}
};
