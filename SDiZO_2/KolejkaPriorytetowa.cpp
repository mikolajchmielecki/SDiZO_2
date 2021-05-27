#include "KolejkaPriorytetowa.h"



/*
tworzy kopiec kopiuj¹c dane z tablicy dynamicznej 
*/
KolejkaPriorytetowa::KolejkaPriorytetowa(Tablica<Struktura*>* tablica) {
	this->tablica = tablica;

	algorytmFloyda();
}



/*
Nie robi nic. tablica jest przenoszona do menu g³ównego
*/
KolejkaPriorytetowa::~KolejkaPriorytetowa() {
}

/*
Dodaje element na koniec kopca i naprawia go
*/
void KolejkaPriorytetowa::dodaj(int liczba) {
	tablica->dodajKoniec(liczba);

	//naprawa kopca
	int indeksPotomka = tablica->getRozmiar() - 1;
	int indeksRodzica = (indeksPotomka - 1) / 2;
	while(indeksPotomka != 0) {
		if (tablica->getTablica()[indeksPotomka] > tablica->getTablica()[indeksRodzica]) {
			tablica->zamien(indeksPotomka, indeksRodzica);
		}
		//nie by³o zamiany
		else {
			break;
		}
		indeksPotomka = indeksRodzica;
		indeksRodzica = (indeksPotomka - 1) / 2;
	}
}


/*
Usuwa korzeñ. W miejsce korzenia wk³ada ostatni element. Naprawia kopiec.
*/
void KolejkaPriorytetowa::usun(int liczba) {
	tablica->zamien(0, tablica->getRozmiar() - 1);
	tablica->usunKoniec();

	int indeksRodzica = 0;
	int lewyPotomek = 1;
	int prawyPotomek = 2;


	while (lewyPotomek < tablica->getRozmiar()) {
		int wiekszyPotomek = -1;

		//automatyczne pominiêcie b³êdu "poza zakresem" dziêki &&
		if (prawyPotomek < tablica->getRozmiar() && tablica->getTablica()[prawyPotomek] > tablica->getTablica()[lewyPotomek]) {
			wiekszyPotomek = prawyPotomek;
		}
		else {
			wiekszyPotomek = lewyPotomek;
		}
		
		//naprawa
		if (tablica->getTablica()[wiekszyPotomek] > tablica->getTablica()[indeksRodzica]) {
			tablica->zamien(wiekszyPotomek, indeksRodzica);
			indeksRodzica = wiekszyPotomek;
			lewyPotomek = indeksRodzica * 2 + 1;
			prawyPotomek = indeksRodzica * 2 + 2;
		}
		//koniec naprawy
		else {
			break;
		}
	}
}


/*
Naprawia kopiec wg algorytmu Floyda
*/
void KolejkaPriorytetowa::algorytmFloyda() {
	for (int i = (tablica->getRozmiar() - 2) / 2; i >= 0; i--) {
		naprawKolejkaPriorytetowaDol(i);
	}
}


/*
Naprawia kopiec w dó³ od zadanego indeksu
*/
void KolejkaPriorytetowa::naprawKolejkaPriorytetowaDol(int indeks) {
	int rozmiar = tablica->getRozmiar();
	int lewyPotomekIndeks = -1;
	int prawyPotomekIndeks = -1;
	
	if (indeks * 2 + 1 < rozmiar) {
		lewyPotomekIndeks = indeks * 2 + 1;
	}
	if (indeks * 2 + 2 < rozmiar) {
		prawyPotomekIndeks = indeks * 2 + 2;
	}
	
	//istnieje tylko lewy potomek
	if (prawyPotomekIndeks == -1 && lewyPotomekIndeks != -1) {
		if (tablica->getTablica()[lewyPotomekIndeks] > tablica->getTablica()[indeks]) {
			tablica->zamien(lewyPotomekIndeks, indeks);
		}
	}
	//istniej¹ oba potomki
	else if (lewyPotomekIndeks != -1 && prawyPotomekIndeks != -1) {
		//znajdowanie maksymalnej wartoœci
		int max = tablica->getTablica()[indeks];
		if (tablica->getTablica()[lewyPotomekIndeks] > max) {
			max = tablica->getTablica()[lewyPotomekIndeks];
			
			//najwiêkszy prawy
			if (tablica->getTablica()[prawyPotomekIndeks] > max) {
				tablica->zamien(prawyPotomekIndeks, indeks);
				naprawKolejkaPriorytetowaDol(prawyPotomekIndeks);
				return;
			}

			//najwiêkszy lewy
			tablica->zamien(lewyPotomekIndeks, indeks);
			naprawKolejkaPriorytetowaDol(lewyPotomekIndeks);
			return;
		}

		//najwiêkszy prawy
		if (tablica->getTablica()[prawyPotomekIndeks] > max) {
			tablica->zamien(prawyPotomekIndeks, indeks);
			naprawKolejkaPriorytetowaDol(prawyPotomekIndeks);
			return;
		}
	} 
	//nie ma potomków
	else {
		//nic nie rób
		//koniec rekurencji
		return;
	}
}









