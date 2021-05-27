#pragma once
#include "MySTL.h"
#include "Struktura.h"
#include "IGraf.h"
#include "IAlgorytm.h"

/*
Klasa implementuje metode wyœwietlania wyników dla algorytmów najkrótszej œcie¿ki
*/
class SP : public IAlgorytm {
public:
	virtual string getWynik();
protected:
	Tablica<Struktura*>* wierzcholki;

private:
	string odwrocString(string wejscie);
};

