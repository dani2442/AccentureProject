#include "Combinations2.h"

bool Combinations2::isPrimes = false;
std::vector<int> Combinations2::p = {};


Combinations2::Combinations2():combins(DEPTH)
{
	calculatePrimes();
}

void Combinations2::Start(int noPrime)
{
	this->noPrime = noPrime;
	primes2 = p; primes2.erase(primes2.begin() + noPrime);

	for (int i = 0; i < primes2.size(); i++) {
		combins[0][primes2[i]].steps = 1;
		combins[0][primes2[i]].s = std::string(itos(primes2[i]));
	}

	calculateOperations();

	int count = 0;
	for (int i = 0; i < MAX; i++) {
		if (combins[DEPTH - 1][i].steps < 100)count++;
	}
	if (count == MAX) {
		isOK = true;
		std::string path = "Data/" + itos(p[noPrime])+".csv";
		exportData(path);
		std::cout << p[noPrime] << " - OK"<<std::endl;
	}
	else {
		std::cout << p[noPrime] << " - ERROR "<< count<<std::endl;
	}
	
}

void Combinations2::exportData(std::string& s)
{
	std::ofstream file;
	file.open(s,std::ios::binary);
	Data d;
	int size = sizeof(Data);
	for (int i = 0; i < MAX; i++) {
		d.steps = combins[DEPTH-1][i].steps;
		strcpy_s(d.s, combins[DEPTH-1][i].s.c_str());
		//file << i << "|" <<min[i]<<"|"<< minS[i]<<"\n";
		file.write(reinterpret_cast<char*>(&d), size);
	}
	file.close();
}

void Combinations2::calculateOperations()
{
	for (int i = 2; i < DEPTH+1; i++) {
		std::copy(std::begin(combins[i - 2]), std::end(combins[i - 2]), std::begin(combins[i-1]));
		for (int j = 1; j <= i / 2; j++) {
			_Operations(combins[j-1],combins[i - j-1],combins[i-1]);
		}
	}
}

void Combinations2::_Operations(std::array<Data2,MAX>& a, std::array<Data2,MAX>&b,std::array<Data2,MAX>&c)
{
	for (int i = 0; i < MAX; i++) {
		if (a[i].steps > 100)continue;
		for (int j = 0; j < MAX; j++) {
			if (b[j].steps > 100)continue;
			{
				int n;

				n = i + j;
				if (n < MAX && n>=0) {
					if (c[n].steps > a[i].steps + b[j].steps) {
						c[n].steps = a[i].steps + b[j].steps;
						c[n].s = "(" + a[i].s + "+" + b[j].s + ")";
					}
				}

				n = i - j;
				if (n < MAX && n>=0) {
					if (c[n].steps > a[i].steps + b[j].steps) {
						c[n].steps = a[i].steps + b[j].steps;
						c[n].s = "(" + a[i].s + "-" + b[j].s + ")";
					}
				}

				n = j - i;
				if (n < MAX && n>=0) {
					if (c[n].steps > a[i].steps + b[j].steps) {
						c[n].steps = a[i].steps + b[j].steps;
						c[n].s = "(" + b[j].s + "-" + a[i].s + ")";
					}
				}

				n = i * j;
				if (n < MAX && n>=0) {
					if (c[n].steps > a[i].steps + b[j].steps) {
						c[n].steps = a[i].steps + b[j].steps;
						c[n].s =a[i].s + "*" + b[j].s;
					}
				}
			}
		}
	}
}

std::string Combinations2::itos(int i)
{
	std::stringstream s;
	s << i;
	return s.str();
}
