#pragma once
#include "MySTL.h"
#include "Struktura.h"
#include <math.h>
#include <iostream>


using namespace std;

/*
Klasa s�u�y do ob�sugi operacji wykonywanych na kopcu
Zaimplementowany w wersji tablicowej
Implementacja kopca typu MAX
*/
class KolejkaPriorytetowa {
public:
	KolejkaPriorytetowa(Tablica<Struktura*>* tablica, int wierzcholekStartowy = 0);
	~KolejkaPriorytetowa();
	Struktura* usunMinimum();
	Tablica<Struktura*>* kopiec;
	void naprawGora(int indeks);
	Struktura* getWierzcholek(int wierzcholek);
	int rozmiar;
	int getIndeks(int wierzcholek);
	Tablica<Struktura*>* naprawTablice();
	bool czyWierzcholekWKolejce(int wierzcholek);
private:

	
	/*
	Tablica przechowuj�ca indeks ka�dego wierzcho�ka w kocpcu
	np: indeksy[2] zwraca indeks wierzcho�ka nr 2.
	*/
	Tablica<int>* indeksy;

	/*
	Tablica przechowuje informacj� czy dany wierzcho�ek wci�� zawiera si� w kopcu
	Poczatkowo wszystkie si� zawieraj�, wi�c jest ona wype�niona warto�ciami TRUE
	*/
	Tablica<bool>* czyZawiera;
	void zamien(int indeks1, int indeks2);
};

