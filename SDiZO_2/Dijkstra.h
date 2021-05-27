#pragma once
#include "IAlgorytm.h"
#include<string>
#include "MySTL.h"
#include "Struktura.h"
#include "SP.h"

using namespace std;

/*
Klasa implementująca algorytm Dijkstry
*/
class Dijkstra : public SP {
	Dijkstra(IGraf* graf);
	~Dijkstra();
	virtual void uruchom();
};

