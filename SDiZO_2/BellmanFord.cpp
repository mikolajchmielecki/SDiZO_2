#include "BellmanFord.h"

BellmanFord::BellmanFord(bool zabezpieczenieCyklUjemny) {
	this->zabezpieczenieCyklUjemny = zabezpieczenieCyklUjemny;
}

/*
Zwalnia pamiêæ zajmowan¹ przez tablice struktur 
*/
BellmanFord::~BellmanFord() {
	if (!zwolniony) {
		if (wierzcholki != nullptr) {
			for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
				delete wierzcholki->tablica[i];
			}
			delete wierzcholki;
		}
	}
}

void BellmanFord::inicjalizuj(IGraf* graf) {
	this->graf = graf;
	zwolniony = false;
}

void BellmanFord::zwolnij() {
	if (wierzcholki != nullptr) {
		for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
			delete wierzcholki->tablica[i];
		}
		delete wierzcholki;
	}
	zwolniony = true;
}

void BellmanFord::uruchom() {
	
	// kopiec odleg³oœci oraz poprzedników
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
	}

	// inicjalizacja wierzcho³ka pocz¹tkowego
	wierzcholki->tablica[graf->wierzcholekStartowy]->klucz = 0;

	// pêtla która wykona siê maksymalnie liczbaWierzcho³kow-1
	// mo¿e zostaæ wczeœniej przerwana jeœli nie bêdzie ¿adnej relaksacji
	for (int i = 0; i < graf->liczbaWierzcholkow - 1; i++) {
		graf->inicjalizujIteratorKrawedzi();
		Krawedz* krawedz = graf->nastepnaKrawedz();
		bool zmiana = false;

		// relakacje wszystkich krawêdzi
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

		// je¿eli nie nast¹pi³a ¿adna relsakcja to algorytm koñczymy
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
			// dla testowania nie wyrzucamy wyj¹tku
			if (zabezpieczenieCyklUjemny == false) {
				break;
			}
			else {
				throw exception("[ERROR] Wykryto cykl ujemny lub graf jest niespójny");
			}
		}
		delete krawedz;
		krawedz = graf->nastepnaKrawedz();
	}
}

string BellmanFord::getNazwa() {
	return "Bellman-Ford";
}

