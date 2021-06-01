#pragma once
#include "Typy.h"
#include "MySTL.h"
#include<limits.h>
#include<string>
#include "Struktura.h"
#include "Krawedz.h"

using namespace std;

class IGraf
{
public:
	virtual ~IGraf();
	int wierzcholekStartowy;
	int wierzcholekKoncowy;
	int liczbaKrawedzi;
	int liczbaWierzcholkow;

	virtual void dodajKrawedz(int start, int koniec, int waga) = 0;
	virtual string toString() = 0;

	/*
	Inicjalzuje wszytkie przeplywy na 0
	*/
	virtual void inicjalizujPrzeplywy() = 0;

	/*
	Dodaje zmianê do akualnego przeplywu
	*/
	virtual void zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu) = 0;


	virtual void inicjalizujIteratorKrawedzi() = 0;
	virtual Krawedz* nastepnaKrawedz() = 0;
	virtual void inicjalizujIteratorSasiadow(int wierzcholek) = 0;
	virtual Krawedz* nastepnySasiad() = 0;
protected:
	ReprezentacjaGrafu reprezentacja;
	bool czySkierowany;
	void sprawdzKrawedz(int start, int koniec, int waga);
	string wyrownajString(string liczbaString, int szerokosc);
	string powielZnak(char znak, int powtorzenia);
	TypAlgorytmu typAlgorytmu;
};

