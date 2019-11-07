#pragma once
#include <string>
struct Data {
	int steps;
	char s[30];
};

struct Data2 {
	int steps=9999;
	std::string s;
};

struct Data3 {
	int num;
	int steps=9999;
	std::string s;

};

struct Data4 {
	int num,steps;
	char s[30];
};

struct input {
	long long number;
	int noPrime;
};