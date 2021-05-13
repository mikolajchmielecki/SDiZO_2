#pragma once
#include "Typy.h"
#include "MySTL.h"
#include<limits.h>
#include<string>

using namespace std;

class IGraf
{
public:

	virtual void dodajKrawedz(int start, int koniec, int waga) = 0;
	virtual string toString() = 0;
protected:
	int wierzcholekStartowy;
	int wierzcholekKoncowy;
	int liczbaKrawedzi;
	int liczbaWierzcholkow;
	ReprezentacjaGrafu reprezentacja;
	bool czySkierowany;
	void sprawdzKrawedz();
	string wyrownajString(string liczbaString, int szerokosc);
	string powielZnak(char znak, int powtorzenia);

};

