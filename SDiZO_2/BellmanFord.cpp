#include "BellmanFord.h"

BellmanFord::BellmanFord(IGraf* graf) {
	this->graf = graf;
}

/*
Zwalnia pami�� zajmowan� przez tablice struktur 
*/
BellmanFord::~BellmanFord() {
	if (wierzcholki != nullptr) {
		for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
			delete wierzcholki->tablica[i];
		}
		delete wierzcholki;
	}
}

void BellmanFord::uruchom() {
	
	// kopiec odleg�o�ci oraz poprzednik�w
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
	}

	// inicjalizacja wierzcho�ka pocz�tkowego
	wierzcholki->tablica[0]->klucz = 0;

	// p�tla kt�ra wykona si� maksymalnie liczbaWierzcho�kow-1
	// mo�e zosta� wcze�niej przerwana je�li nie b�dzie �adnej relaksacji
	for (int i = 0; i < graf->liczbaWierzcholkow - 1; i++) {
		graf->inicjalizujIteratorKrawedzi();
		Krawedz* krawedz = graf->nastepnaKrawedz();
		bool zmiana = false;

		// relakacje wszystkich kraw�dzi
		while (krawedz != nullptr) {
			int aktualnaOdleglosc = wierzcholki->tablica[krawedz->koniec]->klucz;
			int nowaOdleglosc = INT_MAX;
			if (wierzcholki->tablica[krawedz->start]->klucz != INT_MAX) {
				nowaOdleglosc = wierzcholki->tablica[krawedz->start]->klucz + krawedz->waga;
			}

			if (aktualnaOdleglosc > nowaOdleglosc) {
				wierzcholki->tablica[krawedz->koniec]->klucz = nowaOdleglosc;
				wierzcholki->tablica[krawedz->koniec]->poprzednik = krawedz->start;
				zmiana = true;
			}
			delete krawedz;
			krawedz = graf->nastepnaKrawedz();

		}

		// je�eli nie nast�pi�a �adna relsakcja to algorytm ko�czymy
		if (zmiana == false) {
			break;
		}
	}

	// sprawdzenie czy nie ma cyklu ujemnego
	graf->inicjalizujIteratorKrawedzi();
	Krawedz* krawedz = graf->nastepnaKrawedz();

	// przechodznie po wszystkich krawedziach
	while (krawedz != nullptr) {
		int odleglosc1 = wierzcholki->tablica[krawedz->koniec]->klucz;
		int odleglosc2 = wierzcholki->tablica[krawedz->start]->klucz;
		if (odleglosc1 > odleglosc2 + krawedz->waga) {
			throw exception("[ERROR] Wykryto cykl ujemny");
		}
		delete krawedz;
		krawedz = graf->nastepnaKrawedz();
	}
}

