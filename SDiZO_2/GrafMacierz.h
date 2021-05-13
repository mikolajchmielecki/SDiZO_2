#pragma once
#include "IGraf.h"

class GrafMacierz : public IGraf
{
public:
	GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany);
	~GrafMacierz();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
private:
	Tablica<Tablica<int>*>* macierz;
};

