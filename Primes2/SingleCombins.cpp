#include "SingleCombins.h"

bool SingleConbins::isPrimes = false;
std::vector<int> SingleConbins::p = {};

SingleConbins::SingleConbins()
{
	calculatePrimes();
}

void SingleConbins::Start(int noPrime)
{
	this->noPrime = noPrime;
	primes2 = p; primes2.erase(primes2.begin() + noPrime);

	for (int i = 0; i < primes2.size(); i++) {
		combins[0].push_back({ primes2[i],1,itos(primes2[i]) });
	}

	calculateOperations();

	std::string path = "Combinaciones/";
	exportData(path);
}

void SingleConbins::exportData(std::string& s)
{
	for (int j = 0; j < DEPTH; j++) {
		std::ofstream file;
		std::string t = s + itos(p[noPrime]) + "_" + itos(j) + ".csv";
		file.open(t,std::ios::binary);
		Data4 d;
		int size = sizeof(Data4);
		for (int i = 0; i < combins[j].size(); i++) {
			d.steps = combins[j][i].steps;
			d.num = combins[j][i].num;
			strcpy_s(d.s, combins[j][i].s.c_str());
			//file << i << "|" <<min[i]<<"|"<< minS[i]<<"\n";
			file.write(reinterpret_cast<char*>(&d), size);
		}
		file.close();
	}
}


void SingleConbins::calculateOperations()
{
	for (int i = 2; i < DEPTH+1; i++) {
		for (int j = 1; j <= i / 2; j++) {
			_Operations(combins[j-1],combins[i - j-1],combins[i-1]);
		}
	}
}

void SingleConbins::check(Data3& n, std::vector<Data3>& vec)
{
	bool add = true;
	for (int i = 0; i < vec.size(); i++) {
		if (n.num == vec[i].num) {
			add = false;
			if (n.steps < vec[i].steps) {
				vec[i] = n;
			}
		}
	}
	if (add) {
		vec.push_back(n);
	}
}

void SingleConbins::_Operations(std::vector<Data3>& a, std::vector<Data3>& b, std::vector<Data3>& c)
{
	Data3 d;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			{
				d = { a[i].num + b[j].num,a[i].steps + b[j].steps,"(" + a[i].s + "+" + b[j].s + ")" };
				check(d, c);
			}

			if(a[i].num-b[j].num>0){
				d = { a[i].num - b[j].num,a[i].steps + b[j].steps,"(" + a[i].s + "-" + b[j].s + ")" };
				check(d, c);
			}

			if(b[j].num-a[i].num>0){
				d = { b[j].num-a[i].num ,a[i].steps + b[j].steps,"(" + b[j].s + "-" + a[i].s + ")" };
				check(d, c);
			}

			{
				d = { a[i].num * b[j].num,a[i].steps + b[j].steps, a[i].s + "*" + b[j].s };
				check(d, c);
			}
		}
	}
}
