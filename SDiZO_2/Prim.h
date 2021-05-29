#pragma once
#include "IAlgorytm.h"
#include "IGraf.h"
#include "KolejkaPriorytetowa.h"
#include "MST.h"

class Prim : public MST {
public:
	Prim(IGraf* graf);
	~Prim();
	virtual void uruchom();

};


