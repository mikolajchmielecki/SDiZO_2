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
	Tablica przechowuj¹ca indeks ka¿dego wierzcho³ka w kocpcu
	np: indeksy[2] zwraca indeks wierzcho³ka nr 2.
	*/
	Tablica<int>* indeksy;

	/*
	Tablica przechowuje informacjê czy dany wierzcho³ek wci¹¿ zawiera siê w kopcu
	Poczatkowo wszystkie siê zawieraj¹, wiêc jest ona wype³niona wartoœciami TRUE
	*/
	Tablica<bool>* czyZawiera;
	void zamien(int indeks1, int indeks2);
};

