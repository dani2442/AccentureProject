#pragma once

#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <iostream>

#include "Constants.h"
#include "Data.h"

class Combinations2
{
	public:
	Combinations2();
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


private:
	int noPrime;
	std::vector<int> primes2;

	std::vector<std::array<Data2, MAX>> combins;
	
	void calculateOperations();

	void _Operations(std::array<Data2,MAX>&a,std::array<Data2,MAX>&b,std::array<Data2,MAX>&c);

	std::string itos(int i);
};

