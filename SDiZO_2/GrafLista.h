#pragma once
#include "IGraf.h"
#include "MySTL.h"

struct Sasiad {
	int numerWierzcholka;
	int waga;
};

class GrafLista : public IGraf
{
public:
	GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany);
	~GrafLista();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
private:
	Tablica<Lista<Sasiad*>*>* tablicaList;
};

