
#include "Decompose2.h"

bool Decompose2::isPrimes = false;
std::vector<int> Decompose2::p = {};
std::vector<Data4> Decompose2::combins[PRIMES][DEPTH] = {};
std::vector<Data> Decompose2::numeros[PRIMES] = { };

Decompose2::Decompose2()
{

	Init();
	read2();
	read1();
	
}

void Decompose2::decomp(long long n, int noPrime)
{
	for (int i = 0; i < p.size(); i++) {
		if (p[i] == noPrime) {
			this->noPrime = i;
		}
	}

	min = 9999;
	std::string s("()");
	if(n>MAX)
	_Operations(0, n, s);
	else {
		min = numeros[this->noPrime][n].steps;
		minS = std::string(numeros[this->noPrime][n].s);
	}
}

void Decompose2::_Operations(int count, long long a, std::string& s)
{
	for (int i = 0; i < DEPTH - count; i++) {
		for (int j = 0; j < combins[noPrime][i].size(); j++) {
			long long n;
			std::string nt;
			{
				n = a + combins[noPrime][i][j].num;
				nt = s;
				int m=nt.find_first_not_of('(');
				nt.insert(m, "()-" + std::string(combins[noPrime][i][j].s));
				if (n > 0 && n < MAX) {
					int nmin = count + numeros[noPrime][n].steps + combins[noPrime][i][j].steps;
					if (min > nmin) {
						int m=nt.find_first_not_of('(');
						minS = nt.insert(m, numeros[noPrime][n].s);
						min = nmin;
					}
				}
				else {
					_Operations(count + combins[noPrime][i][j].steps, n, nt);
				}
			}
			{
				n = a - combins[noPrime][i][j].num;
				nt = s;
				int m=nt.find_first_not_of('(');
				nt.insert(m, "()+" + std::string(combins[noPrime][i][j].s));
				if (n > 0 && n < MAX) {
					int nmin = count + numeros[noPrime][n].steps + combins[noPrime][i][j].steps;
					if (min > nmin) {
						int m=nt.find_first_not_of('(');
						minS = nt.insert(m, numeros[noPrime][n].s);
						min = nmin;
					}
				}
				else {
					_Operations(count + combins[noPrime][i][j].steps, n, nt);
				}
			}
			{
				if (a % combins[noPrime][i][j].num == 0) {
					n = a / combins[noPrime][i][j].num;
					nt = s;
					int m=nt.find_first_not_of('(');
					nt.insert(m, "()*" + std::string(combins[noPrime][i][j].s));
					if (n > 0 && n < MAX) {
						int nmin = count + numeros[noPrime][n].steps + combins[noPrime][i][j].steps;
						if (min > nmin) {
							int m=nt.find_first_not_of('(');
							minS = nt.insert(m, numeros[noPrime][n].s);
							min = nmin;
						}
					}
					else {
						_Operations(count + combins[noPrime][i][j].steps, n, nt);
					}
				}
			}

		}
	}
}

void Decompose2::read1()
{
	int size = sizeof(Data);
	for (int i = 0; i < p.size(); i++) {
		std::string s = "Data/" + itos(p[i])+".csv";
		std::ifstream in(s.c_str(),std::ios::binary);

		int j = 0;
		while (in.peek()!=EOF) {
			in.read(reinterpret_cast<char*>(&numeros[i][j]), size);
			j++;
		}
		in.close();
	}
}

void Decompose2::read2()
{
	
	int size = sizeof(struct Data4);
	
	for (int i = 0; i < p.size(); i++) {
		for (int j =0; j < DEPTH; j++) {
			std::string s = "Combinaciones/" + itos(p[i]) + "_" + itos(j) + ".csv";
			std::ifstream in(s.c_str(),std::ios::binary);

			int k = 0;
			while (!in.eof()) {
				Data4 temp;
				in.read(reinterpret_cast<char*>(&temp), size);
				combins[i][j].push_back(temp);
				k++;
			}
			in.close();
		}
	}
}
