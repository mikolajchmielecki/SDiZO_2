#pragma once
#include <string>

using namespace std;

class Krawedz {
public:
	Krawedz(int start, int koniec, int waga, int przeplyw = 0);
	int start;
	int koniec;
	int waga;
	int przeplyw;
	string toString();
};

