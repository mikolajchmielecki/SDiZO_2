#pragma once
#include<string>
#include "IGraf.h"
#include "Struktura.h"
#include "MySTL.h"

using namespace std;

class IAlgorytm {
public:
	virtual void inicjalizuj(IGraf* graf) = 0;
	virtual void zwolnij() = 0;
	virtual void uruchom() = 0;
	virtual string getWynik() = 0;
	virtual string getNazwa() = 0;

protected:
	Tablica<Struktura*>* wierzcholki;
	IGraf* graf;
	bool zwolniony = true;
};

