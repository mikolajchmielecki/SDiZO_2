#pragma once
#include "GrafLista.h"
#include "GrafMacierz.h"
#include "Typy.h"
#include "IGraf.h"
#include <random>
#include<limits>

class LosowyGraf {
public:
	LosowyGraf(TypAlgorytmu typAlgorytmu, ReprezentacjaGrafu reprezentacja, int liczbaWierzcholkow, float gestosc);
	IGraf* losuj();

private:
	int getLosowaWaga();
	int getLosowaLiczba(int min, int max);
	GrafMacierz* losujSP();
	GrafMacierz* losujMF();
	GrafMacierz* losujMST();
	bool czySkierowany;
	bool czyDuplikaty;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	int wierzcholekStartowy;
	int wierzcholekKoncowy;
	TypAlgorytmu typAlgorytmu;
	ReprezentacjaGrafu reprezentacja;

};

