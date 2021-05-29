#pragma once

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
	

private:
	string odwrocString(string wejscie);
};

