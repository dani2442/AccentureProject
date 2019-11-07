#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Constants.h"
#include "Combinations2.h"
#include "Decompose2.h"

#include "SingleCombins.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

void calculate_10e6() {
	Combinations2::calculatePrimes();
	int nprimes = Combinations2::p.size(); // number of primes [1-100]

	std::vector<std::thread> thread(nprimes); // Create threads

	std::vector<Combinations2> c(nprimes); // Combinations without one prime

	for (int i = 0; i < thread.size(); i++) {
		thread[i] = std::thread(&Combinations2::Start, &c[i], i); // Start threads
	}

	for (int i = 0; i < thread.size(); i++) {
		thread[i].join(); // Join threads
	}
}

void combinaciones() {
	SingleConbins::calculatePrimes();
	int nprimes = SingleConbins::p.size(); // number of primes [1-100]

	std::vector<std::thread> thread(nprimes); // Create threads

	std::vector<SingleConbins> c(nprimes); // Combinations without one prime

	for (int i = 0; i < thread.size(); i++) {
		thread[i] = std::thread(&SingleConbins::Start, &c[i], i); // Start threads
	}

	for (int i = 0; i < thread.size(); i++) {
		thread[i].join(); // Join threads
	}

}

static std::vector<input> datain;
static std::vector<Data2> dataout;

void ReadData(std::string s){
	std::string line;
	std::ifstream in(s);
	char c; int a;
	std::getline(in, line);
	input i;
	while (in>>a>>c>>i.number>>c>>i.noPrime) {
		datain.push_back(i);
	}
	in.close();
}
void ExportData(std::string s) {
	std::ofstream out(s);
	for (int i = 0; i < dataout.size(); i++) {
		out << "02572508G|" << i + 1 << "|" << dataout[i].steps << "|" << dataout[i].s << "\n";
	}
	out.close();
}

void execute() {

	std::vector<std::thread> thread(datain.size()); // Create threads

	//std::vector<Decompose2> c(datain.size()); // Combinations without one prime
	/*
	for (int i = 0; i < thread.size(); i++) {
		thread[i] = std::thread(&Decompose2::decomp,&c[i], datain[i].number,datain[i].noPrime); // Start threads
	}

	for (int i = 0; i < thread.size(); i++) {
		thread[i].join(); // Join threads
	}*/
	Decompose2 d;
	for (int i = 0; i <datain.size(); i++) {
		d.decomp(datain[i].number, datain[i].noPrime);
		Data2 data;
		data.s = d.minS;
		data.steps = d.min;

		dataout.push_back(data);
		d.Reset();
	}
}


int main() {

	std::cout << "1- Reading data...\n";
	ReadData("TEST.txt");
	std::cout << "2- Executing...\n";
	// Only needs to be computed once

	auto t0 = Time::now(); // Start timer
	//combinaciones();
	//calculate_10e6();
	execute();

	auto t1 = Time::now(); // Finish timer
	fsec fs = t1 - t0;

	std::cout << "Time: " << fs.count()<<std::endl;
	std::cout << "finish...press enter\n";

	ExportData("SCORE.txt");
}