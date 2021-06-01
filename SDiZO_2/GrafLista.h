#pragma once
#include "IGraf.h"
#include "MySTL.h"
#include "Typy.h"

struct Sasiad {
	int numerWierzcholka;
	int waga;
	int przeplyw;
};

class GrafLista : public IGraf
{
public:
	GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypAlgorytmu typAlgorytmu = TypAlgorytmu::DEFAULT);
	virtual ~GrafLista();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
	virtual void inicjalizujIteratorKrawedzi();
	virtual Krawedz* nastepnaKrawedz();
	virtual void inicjalizujIteratorSasiadow(int wierzcholek);
	virtual Krawedz* nastepnySasiad();
	virtual void inicjalizujPrzeplywy();
	virtual void zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu);

private:
	bool czySasiedzi(int start, int koniec);
	Tablica<Lista<Sasiad*>*>* tablicaList;
	int iteratorRzad;
	ElementListy<Sasiad*>* iteratorKolumna;
	bool czyDuplikaty;
};

