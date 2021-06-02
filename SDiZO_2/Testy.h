#pragma once
#include "IAlgorytm.h"
#include "LosowyGraf.h"
#include "Typy.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "FordFulkerson.h"
#include "BellmanFord.h"
#include "Prim.h"
#include <windows.h>
#include <iomanip>
#include<fstream>

class Testy {
public:
	void uruchomTesty();
private:
	void testujAlgorytm(IAlgorytm* algorytm, int maksymalnaLiczbaWierzcholkow, TypAlgorytmu typAlgorytmu);
	void testujPrzypadek(IAlgorytm* algorytm, float gestosc, int maksymalnaLiczbaWierzcholkow, ReprezentacjaGrafu reprezentacja, TypAlgorytmu typAlgorytmu);
	double getSredniCzas(IAlgorytm* algorytm, LosowyGraf* losowyGraf);
	long long int read_QPC();
	long long int frequency;
	string wynikToString(int liczbaRozmiarow, int maksymalnyRozmiar, double* srednieCzasy);
	void zapisz(string nazwaPliku, string dane);
};

