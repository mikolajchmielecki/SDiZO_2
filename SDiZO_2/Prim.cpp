#include "Prim.h"


Prim::Prim(IGraf* graf) {
	this->graf = graf;
}

Prim::~Prim() {
	for (int i = 0; i < krawedzieMST->getRozmiar(); i++) {
		delete krawedzieMST->tablica[i];
	}
	delete krawedzieMST;

	// zwalnianie pamiêci zajmowanej prze struktury
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		delete wierzcholki->tablica[i];
	}
	delete wierzcholki;
}

void Prim::uruchom() {
	// kopiec odleg³oœci oraz poprzedników
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
		wierzcholki->tablica[i]->wierzcholek = i;
	}

	// inicjalizacja wierzcho³ka pocz¹tkowego
	wierzcholki->tablica[0]->klucz = 0;

	KolejkaPriorytetowa* kolejka = new KolejkaPriorytetowa(wierzcholki);

	while (kolejka->rozmiar > 0) {
		Struktura* minimum = kolejka->usunMinimum();

		graf->inicjalizujIteratorSasiadow(minimum->wierzcholek);
		Krawedz* krawedz = graf->nastepnySasiad();

		// sprawdzanie kazdego sasiada
		while (krawedz != nullptr) {

			int sasiad = krawedz->koniec;
			int staraOdleglosc = kolejka->getWierzcholek(sasiad)->klucz;
			int nowaOdleglosc = krawedz->waga;
			if (kolejka->czyWierzcholekWKolejce(sasiad) && staraOdleglosc > nowaOdleglosc) {
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


	//przygotowtywanie wyniku koñcowego
	// rezerwacja miejsca na krawedzie MST
	krawedzieMST = new Tablica<Krawedz*>(graf->liczbaWierzcholkow - 1);

	int iteratorKrawedzi = 0;
	// wyznaczanie krawedzi wchodzacych w sk³ad MST
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		int sasiad = wierzcholki->tablica[i]->poprzednik;
		if (sasiad != -1) {

			// pocz¹tek krawedzi to mniejszy wierzcholek
			int start = -1;
			int koniec = -1;
			if (i < sasiad) {
				start = i;
				koniec = sasiad;
			}
			else {
				start = sasiad;
				koniec = i;
			}
			Krawedz* krawedz = new Krawedz(start, koniec, wierzcholki->tablica[i]->klucz);
			krawedzieMST->tablica[iteratorKrawedzi] = krawedz;
			iteratorKrawedzi++;
		}
	}

}




