#pragma once
#include "MST.h"
#include "IGraf.h"
#include "Zbior.h"

class Kruskal : public MST {
public:
	Kruskal(IGraf* graf);
	~Kruskal();
	virtual void uruchom();
private:
	Tablica<Krawedz*>* krawedzie;
};

