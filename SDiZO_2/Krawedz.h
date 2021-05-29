#pragma once
#include <string>

using namespace std;

class Krawedz {
public:
	Krawedz(int start, int koniec, int waga);
	int start;
	int koniec;
	int waga;
	string toString();
};

