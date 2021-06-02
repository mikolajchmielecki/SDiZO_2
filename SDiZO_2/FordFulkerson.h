#pragma once
#include "IAlgorytm.h"
#include <string>
#include "IGraf.h"
#include "Kolejka.h"

using namespace std;

class FordFulkerson : public IAlgorytm {
public:
	FordFulkerson(TrybPrzeszukiwania tryb);
	~FordFulkerson();
	virtual void uruchom();
	virtual string getWynik();
	virtual void inicjalizuj(IGraf* graf);
	virtual void zwolnij();
	virtual string getNazwa();
private:
	void inicjalizujTablicePrzeplywow();
	TrybPrzeszukiwania tryb;
	int maksymalnyPrzeplyw;
	bool znajdzSciezkeRozszerzajaca();
	void wstawSasiadow(int wierzcholek, Kolejka* kolejka);
};
