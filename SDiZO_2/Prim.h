#pragma once
#include "IAlgorytm.h"
#include "IGraf.h"
#include "KolejkaPriorytetowa.h"
#include "MST.h"

class Prim : public MST {
public:
	Prim();
	~Prim();
	virtual void uruchom();
	virtual void inicjalizuj(IGraf* graf);
	virtual void zwolnij();
	virtual string getNazwa();
};


