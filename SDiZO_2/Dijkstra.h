#pragma once
#include "IAlgorytm.h"
#include<string>
#include "MySTL.h"
#include "Struktura.h"
#include "SP.h"
#include "KolejkaPriorytetowa.h"

using namespace std;

/*
Klasa implementuj�ca algorytm Dijkstry
*/
class Dijkstra : public SP {
public:
	Dijkstra(IGraf* graf, bool zabezpieczenieMinus);
	~Dijkstra();
	virtual void uruchom();
	string info;
private:
	bool zabezpieczenieMinus;
};

