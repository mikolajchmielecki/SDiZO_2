#pragma once
#include<string>
#include "IGraf.h"

using namespace std;

class IAlgorytm {
public:
	virtual void uruchom() = 0;
	virtual string getWynik() = 0;

protected:
	IGraf* graf;
};

