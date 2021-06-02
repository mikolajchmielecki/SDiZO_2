#pragma once
#include "IAlgorytm.h"
#include<string>
#include "MySTL.h"
#include "Struktura.h"
#include "SP.h"

using namespace std;

class BellmanFord : public SP {
public:
	BellmanFord(bool zabezpieczenieCyklUjemny = true);
	~BellmanFord();
	virtual void inicjalizuj(IGraf* graf);
	virtual void zwolnij();
	virtual void uruchom();
	virtual string getNazwa();
private:
	bool zabezpieczenieCyklUjemny;
};

