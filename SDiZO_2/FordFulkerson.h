#pragma once
#include "IAlgorytm.h"
#include <string>
#include "IGraf.h"
#include "Kolejka.h"

using namespace std;

class FordFulkerson : public IAlgorytm {
public:
	FordFulkerson(IGraf* graf, TrybPrzeszukiwania tryb);
	~FordFulkerson();
	virtual void uruchom();
	virtual string getWynik();
private:
	void inicjalizujTablicePrzeplywow();
	TrybPrzeszukiwania tryb;
	int maksymalnyPrzeplyw;
	bool znajdzSciezkeRozszerzajaca();
	void wstawSasiadow(int wierzcholek, Kolejka* kolejka);
};
