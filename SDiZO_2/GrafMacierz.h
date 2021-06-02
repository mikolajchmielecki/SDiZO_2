#pragma once
#include "IGraf.h"
#include "Typy.h"
#include "GrafLista.h"

class GrafMacierz : public IGraf {
public:
	GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypProblemu typAlgorytmu = TypProblemu::DEFAULT);
	virtual ~GrafMacierz();
	virtual string toString();
	virtual void dodajKrawedz(int start, int koniec, int waga);
	virtual void inicjalizujIteratorKrawedzi();
	virtual Krawedz* nastepnaKrawedz();
	virtual void inicjalizujIteratorSasiadow(int wierzcholek);
	virtual Krawedz* nastepnySasiad();
	virtual void inicjalizujPrzeplywy();
	virtual string getNazwa();
	virtual void zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu);
	GrafLista* getGrafLista();
	Tablica<Tablica<int>*>* getMacierz();
private:
	Tablica<Tablica<int>*>* macierz;
	Tablica<Tablica<int>*>* macierzPrzeplywow;
	int iteratorKolumna;
	int iteratorRzad;
	int iteratorWierzcholek;
	int iteratorSasiad;
	bool czyDuplikaty;
};

