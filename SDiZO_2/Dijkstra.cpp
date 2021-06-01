#include "Dijkstra.h"


/*
zabezpieczenieMinus - je�eli true to przerywa dzia�anie algorytmu w momencie wykrycia ujemnej wagi
*/
Dijkstra::Dijkstra(IGraf* graf, bool zabezpieczenieMinus) {
	this->graf = graf;
	this->zabezpieczenieMinus = zabezpieczenieMinus;
	info = "Nie wykryto ujemnej wagi.";
}

Dijkstra::~Dijkstra() {
	// zwalnianie pami�ci zajmowanej prze struktury
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		delete wierzcholki->tablica[i];
	}
	delete wierzcholki;
}

void Dijkstra::uruchom() {
	// kopiec odleg�o�ci oraz poprzednik�w
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
		wierzcholki->tablica[i]->wierzcholek = i;
	}

	// inicjalizacja wierzcho�ka pocz�tkowego
	wierzcholki->tablica[graf->wierzcholekStartowy]->klucz = 0;

	KolejkaPriorytetowa* kolejka = new KolejkaPriorytetowa(wierzcholki, graf->wierzcholekStartowy);

	while (kolejka->rozmiar > 0) {
		Struktura* minimum = kolejka->usunMinimum();

		graf->inicjalizujIteratorSasiadow(minimum->wierzcholek);
		Krawedz* krawedz = graf->nastepnySasiad();

		// sprawdzanie kazdego sasiada
		while (krawedz != nullptr) {

			if (krawedz->waga < 0) {
				info = "Uwaga - wykryto ujemn� wag�. Wynik mo�e by� nieprawid�owy";
				if (zabezpieczenieMinus) {
					throw exception("[ERROR] Wykryto ujemn� wag�");
				}

			}

			int sasiad = krawedz->koniec;
			int staraOdleglosc = kolejka->getWierzcholek(sasiad)->klucz;
			int nowaOdleglosc = kolejka->getWierzcholek(minimum->wierzcholek)->klucz + krawedz->waga;
			if (staraOdleglosc > nowaOdleglosc) {
				// relaksacja
				kolejka->getWierzcholek(sasiad)->klucz = nowaOdleglosc;
				kolejka->getWierzcholek(sasiad)->poprzednik = minimum->wierzcholek;
				kolejka->naprawGora(kolejka->getIndeks(sasiad));
			}
			delete krawedz;
			krawedz = graf->nastepnySasiad();
		}
	}

	wierzcholki = kolejka->naprawTablice();
	delete kolejka;
}
