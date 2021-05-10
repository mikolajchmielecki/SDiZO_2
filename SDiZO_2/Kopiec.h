#pragma once
#include "TablicaDynamiczna.h"
#include "IPotomkowie.h"
#include "WyswietlanieDrzewa.h"
#include "IStrukturyDrzewiaste.h"


using namespace std;

/*
Klasa s³u¿y do ob³sugi operacji wykonywanych na kopcu
Zaimplementowany w wersji tablicowej
Implementacja kopca typu MAX
*/
class Kopiec : public IStrukturyDrzewiaste {
public:
	Kopiec(TablicaDynamiczna* tablica);
	Kopiec();
	~Kopiec();
	virtual void dodaj(int liczba);
	virtual void usun(int liczba = 0);
	virtual int wyszukaj(int liczba, bool wyswietlanie);
	virtual void wyswietl();
private:
	TablicaDynamiczna* tablica;
	void algorytmFloyda();
	void naprawKopiecDol(int);
};

