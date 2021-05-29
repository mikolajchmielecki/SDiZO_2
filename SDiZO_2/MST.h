#pragma once

#include "Struktura.h"
#include "IGraf.h"
#include "IAlgorytm.h"

class MST : public IAlgorytm {
public:
	virtual string getWynik();
protected:
	Tablica<Krawedz*>* krawedzieMST;
};

