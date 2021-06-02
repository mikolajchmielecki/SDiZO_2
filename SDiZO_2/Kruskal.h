#pragma once
#include "MST.h"
#include "IGraf.h"
#include "Zbior.h"

class Kruskal : public MST {
public:
	Kruskal();
	~Kruskal();
	virtual void uruchom();
	virtual void inicjalizuj(IGraf* graf);
	virtual void zwolnij();
	virtual string getNazwa();
private:
	Tablica<Krawedz*>* krawedzie;
};

