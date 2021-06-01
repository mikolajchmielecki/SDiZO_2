#pragma once
#include "IGraf.h"
#include "Typy.h"

class GrafMacierz : public IGraf {
public:
	GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypAlgorytmu typAlgorytmu = TypAlgorytmu::DEFAULT);
	virtual ~GrafMacierz();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
	virtual void inicjalizujIteratorKrawedzi();
	virtual Krawedz* nastepnaKrawedz();
	virtual void inicjalizujIteratorSasiadow(int wierzcholek);
	virtual Krawedz* nastepnySasiad();
	virtual void inicjalizujPrzeplywy();
	virtual void zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu);
private:
	Tablica<Tablica<int>*>* macierz;
	Tablica<Tablica<int>*>* macierzPrzeplywow;
	int iteratorKolumna;
	int iteratorRzad;
	int iteratorWierzcholek;
	int iteratorSasiad;
	bool czyDuplikaty;
};

