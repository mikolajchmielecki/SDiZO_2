#include "KolejkaPriorytetowa.h"



/*
Tworzy kopiec kopiuj¹c dane z tablicy dynamicznej 
Zak³ada, ¿e pocz¹tkowo kopiec jest zbudowany
W u¿ywanych algorytmach tak faktycznie jest
*/
KolejkaPriorytetowa::KolejkaPriorytetowa(Tablica<Struktura*>* tablica, int wierzcholekStartowy) {
	this->kopiec = tablica;
	this->rozmiar = tablica->getRozmiar();

	// tablica która przechowuje indeksy wierzcho³ków w kopcu
	// indeksy[wierzcholek] zwraca indeks danego wierzcho³ka w kopcu
	indeksy = new Tablica<int>(tablica->getRozmiar());
	for (int i = 0; i < indeksy->getRozmiar(); i++) {
		indeksy->tablica[i] = i;
	}

	czyZawiera = new Tablica<bool>(tablica->getRozmiar());
	for (int i = 0; i < czyZawiera->getRozmiar(); i++) {
		czyZawiera->tablica[i] = true;
	}

	zamien(0, wierzcholekStartowy);
}



/*

*/
KolejkaPriorytetowa::~KolejkaPriorytetowa() {
	delete indeksy;
	delete czyZawiera;
}


/*
Zwraca korzeñ
Zamienia ostatni element z korzeniem. Naprawia kopiec.
*/
Struktura* KolejkaPriorytetowa::usunMinimum() {
	Struktura* wynik = kopiec->tablica[0];

	czyZawiera->tablica[wynik->wierzcholek] = false;

	// zamiana korzenia z z koñcem
	zamien(0, rozmiar-1);

	rozmiar--;

	int indeksRodzica = 0;
	int lewyPotomek = 1;
	int prawyPotomek = 2;


	while (lewyPotomek < rozmiar) {
		int mniejszyPotomek = -1;

		//automatyczne pominiêcie b³êdu "poza zakresem" dziêki &&
		if (prawyPotomek < rozmiar && kopiec->tablica[prawyPotomek]->klucz < kopiec->tablica[lewyPotomek]->klucz) {
			mniejszyPotomek = prawyPotomek;
		}
		else {
			mniejszyPotomek = lewyPotomek;
		}
		
		//naprawa
		if (kopiec->tablica[mniejszyPotomek]->klucz < kopiec->tablica[indeksRodzica]->klucz) {
			zamien(mniejszyPotomek, indeksRodzica);
			indeksRodzica = mniejszyPotomek;
			lewyPotomek = indeksRodzica * 2 + 1;
			prawyPotomek = indeksRodzica * 2 + 2;
		}
		//koniec naprawy
		else {
			break;
		}
	}

	return wynik;
}


/*
Naprawia kopiec w górê od zadanego wierzcho³ka
*/
void KolejkaPriorytetowa::naprawGora(int indeks) {
	int lewyPotomekIndeks = -1;
	int prawyPotomekIndeks = -1;

	// zakoñczenie wywo³ania rekurencyjnego
	if (indeks == 0) {
		return;
	}

	int rodzic = (indeks - 1) / 2;

	int brat = -1;

	// brat jest lewym potomkiem
	if (rodzic*2+1 != indeks) {
		brat = rodzic * 2 + 1;
	}

	// brat jest prawym potomkiem
	if (rodzic * 2 + 2 != indeks) {
		brat = rodzic * 2 + 2;
	}

	int mniejszyPotomek = -1;
	// ma brata
	if (brat < rozmiar) {
		
		// porównanie rodzeñstwa
		if (kopiec->tablica[brat]->klucz < kopiec->tablica[indeks]->klucz) {
			mniejszyPotomek = brat;
		}
		else {
			mniejszyPotomek = indeks;
		}
	}
	else {
		mniejszyPotomek = indeks;
	}

	// porównanie potomka z rodzicem
	if (kopiec->tablica[indeks]->klucz < kopiec->tablica[rodzic]->klucz) {
		zamien(indeks, rodzic);
		naprawGora(rodzic);
	}
}

Struktura* KolejkaPriorytetowa::getWierzcholek(int wierzcholek) {
	return kopiec->tablica[indeksy->tablica[wierzcholek]];
}

int KolejkaPriorytetowa::getIndeks(int wierzcholek) {
	return indeksy->tablica[wierzcholek];
}

/*
Przywraca pocz¹tkow¹ kolejnoœæ wierzcho³ków w tablicy struktur
*/
Tablica<Struktura*>* KolejkaPriorytetowa::naprawTablice() {
	Tablica<Struktura*>* tablicaWynikowa = new Tablica<Struktura*>(kopiec->getRozmiar());
	for (int i = 0; i < kopiec->getRozmiar(); i++) {
		tablicaWynikowa->tablica[i] = kopiec->tablica[indeksy->tablica[i]];
	}
	delete kopiec;
	return tablicaWynikowa;
}

bool KolejkaPriorytetowa::czyWierzcholekWKolejce(int wierzcholek) {
	return czyZawiera->tablica[wierzcholek];
}

/*
Zamienia struktury miejscami
I zmienia indeksy dla tych dwóch wierzcho³ków
*/
void KolejkaPriorytetowa::zamien(int indeks1, int indeks2) {
	swap(indeksy->tablica[kopiec->tablica[indeks1]->wierzcholek], indeksy->tablica[kopiec->tablica[indeks2]->wierzcholek]);
	swap(kopiec->tablica[indeks1], kopiec->tablica[indeks2]);
}














