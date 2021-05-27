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
	virtual ~GrafLista();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
	virtual void inicjalizujIteratorKrawedzi();
	virtual Krawedz* nastepnaKrawedz();
	virtual void inicjalizujIteratorSasiadow(int wierzcholek);
	virtual Krawedz* nastepnySasiad();

private:
	Tablica<Lista<Sasiad*>*>* tablicaList;
	int iteratorRzad;
	ElementListy<Sasiad*>* iteratorKolumna;
};

