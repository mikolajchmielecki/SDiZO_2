#include "Prim.h"


Prim::Prim() {
	
}

Prim::~Prim() {
	if (!zwolniony) {
		for (int i = 0; i < krawedzieMST->getRozmiar(); i++) {
			delete krawedzieMST->tablica[i];
		}
		delete krawedzieMST;

		// zwalnianie pamięci zajmowanej prze struktury
		for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
			delete wierzcholki->tablica[i];
		}
		delete wierzcholki;
	}
}

void Prim::uruchom() {
	// kopiec odległości oraz poprzedników
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
		wierzcholki->tablica[i]->wierzcholek = i;
	}

	// inicjalizacja wierzchołka początkowego
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


	//przygotowtywanie wyniku końcowego
	// rezerwacja miejsca na krawedzie MST
	krawedzieMST = new Tablica<Krawedz*>(graf->liczbaWierzcholkow - 1);

	int iteratorKrawedzi = 0;
	// wyznaczanie krawedzi wchodzacych w skład MST
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		int sasiad = wierzcholki->tablica[i]->poprzednik;
		if (sasiad != -1) {

			// początek krawedzi to mniejszy wierzcholek
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

void Prim::inicjalizuj(IGraf* graf) {
	this->graf = graf;
	zwolniony = false;
}

void Prim::zwolnij() {
	zwolniony = true;
	for (int i = 0; i < krawedzieMST->getRozmiar(); i++) {
		delete krawedzieMST->tablica[i];
	}
	delete krawedzieMST;

	// zwalnianie pamięci zajmowanej prze struktury
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		delete wierzcholki->tablica[i];
	}
	delete wierzcholki;
}

string Prim::getNazwa()
{
	return "Prim";
}




