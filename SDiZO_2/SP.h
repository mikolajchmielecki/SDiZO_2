#pragma once

#include "Struktura.h"
#include "IGraf.h"
#include "IAlgorytm.h"

/*
Klasa implementuje metode wy�wietlania wynik�w dla algorytm�w najkr�tszej �cie�ki
*/
class SP : public IAlgorytm {
public:
	virtual string getWynik();
protected:
	

private:
	string odwrocString(string wejscie);
};

