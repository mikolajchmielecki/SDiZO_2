#pragma once
#include "IAlgorytm.h"
#include<string>
#include "MySTL.h"
#include "Struktura.h"
#include "SP.h"

using namespace std;

class BellmanFord : public SP {
public:
	BellmanFord(IGraf* graf);
	~BellmanFord();
	virtual void uruchom();

};

