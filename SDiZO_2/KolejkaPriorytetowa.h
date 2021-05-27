#pragma once
#include "MySTL.h"
#include "Struktura.h"
#include <math.h>
#include <iostream>


using namespace std;

/*
Klasa s³u¿y do ob³sugi operacji wykonywanych na kopcu
Zaimplementowany w wersji tablicowej
Implementacja kopca typu MAX
*/
class KolejkaPriorytetowa {
public:
	KolejkaPriorytetowa(Tablica<Struktura*>* tablica);
	KolejkaPriorytetowa();
	~KolejkaPriorytetowa();
	virtual void dodaj(int liczba);
	virtual void usun(int liczba = 0);
private:
	Tablica<Struktura*>* tablica;
	void algorytmFloyda();
	void naprawKopiecDol(int);
};

