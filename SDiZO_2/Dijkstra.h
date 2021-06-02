#pragma once
#include "IAlgorytm.h"
#include<string>
#include "MySTL.h"
#include "Struktura.h"
#include "SP.h"
#include "KolejkaPriorytetowa.h"

using namespace std;

/*
Klasa implementuj¹ca algorytm Dijkstry
*/
class Dijkstra : public SP {
public:
	Dijkstra(bool zabezpieczenieMinus);
	~Dijkstra();
	virtual void uruchom();
	virtual void inicjalizuj(IGraf* graf);
	virtual void zwolnij();
	virtual string getNazwa();
	string info;
private:
	bool zabezpieczenieMinus;
};

