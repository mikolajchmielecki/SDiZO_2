#include "Kopiec.h"
#include <math.h>
#include <iostream>
#include "KopiecElement.h"
#include "KopiecElementWyszukiwanie.h"


/*
tworzy kopiec kopiuj�c dane z tablicy dynamicznej 
*/
Kopiec::Kopiec(TablicaDynamiczna* tablica) {
	this->tablica = tablica;

	algorytmFloyda();
}

Kopiec::Kopiec() {
	this->tablica = new TablicaDynamiczna();
}


/*
Nie robi nic. tablica jest przenoszona do menu g��wnego
*/
Kopiec::~Kopiec() {
}

/*
Dodaje element na koniec kopca i naprawia go
*/
void Kopiec::dodaj(int liczba) {
	tablica->dodajKoniec(liczba);

	//naprawa kopca
	int indeksPotomka = tablica->getRozmiar() - 1;
	int indeksRodzica = (indeksPotomka - 1) / 2;
	while(indeksPotomka != 0) {
		if (tablica->getTablica()[indeksPotomka] > tablica->getTablica()[indeksRodzica]) {
			tablica->zamien(indeksPotomka, indeksRodzica);
		}
		//nie by�o zamiany
		else {
			break;
		}
		indeksPotomka = indeksRodzica;
		indeksRodzica = (indeksPotomka - 1) / 2;
	}
}


/*
Usuwa korze�. W miejsce korzenia wk�ada ostatni element. Naprawia kopiec.
*/
void Kopiec::usun(int liczba) {
	tablica->zamien(0, tablica->getRozmiar() - 1);
	tablica->usunKoniec();

	int indeksRodzica = 0;
	int lewyPotomek = 1;
	int prawyPotomek = 2;


	while (lewyPotomek < tablica->getRozmiar()) {
		int wiekszyPotomek = -1;

		//automatyczne pomini�cie b��du "poza zakresem" dzi�ki &&
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
Wyszukuje zadan� warto�� w argumencie.
Na �yczenie wy�wietlana jest �cie�ka.
*/
int Kopiec::wyszukaj(int liczba, bool wyswietlanie) {
	int indeks = -1;
	for (int i = 0; i < tablica->getRozmiar(); i++) {
		if (tablica->getTablica()[i] == liczba) {
			indeks = i;
		}
	}
	if (wyswietlanie && indeks != -1) {
		KopiecElementWyszukiwanie* korzen = new KopiecElementWyszukiwanie(tablica, indeks);
		int* sciezka = korzen->sciezka;
		IPotomkowie* Ikorzen = korzen;
		WyswietlanieDrzewa wyswietlanieDrzewa = WyswietlanieDrzewa(Ikorzen);
		wyswietlanieDrzewa.wyswietl(false);
		delete[] sciezka;
	}
	if (indeks == -1) {
		throw exception("\nBrak szukanego elementu\n");
	}
	return indeks;
}

/*
Wyswietla kopiec jako drzewo
Kopiec jest konwertowany na drzewo ze wska�nikami w celu ustandaryzowania algorytmu wy�wietlania dla wszystkich drzew
*/
void Kopiec::wyswietl() {
	if (tablica->getRozmiar() > 0) {
		IPotomkowie* korzen = new KopiecElement(tablica, 0);
		WyswietlanieDrzewa wyswietlanieDrzewa = WyswietlanieDrzewa(korzen);
		wyswietlanieDrzewa.wyswietl(true);
	}
	else {
		cout << "\nBrak element�w do wy�wietlenia\n";
	}
}


/*
Naprawia kopiec wg algorytmu Floyda
*/
void Kopiec::algorytmFloyda() {
	for (int i = (tablica->getRozmiar() - 2) / 2; i >= 0; i--) {
		naprawKopiecDol(i);
	}
}


/*
Naprawia kopiec w d� od zadanego indeksu
*/
void Kopiec::naprawKopiecDol(int indeks) {
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
	//istniej� oba potomki
	else if (lewyPotomekIndeks != -1 && prawyPotomekIndeks != -1) {
		//znajdowanie maksymalnej warto�ci
		int max = tablica->getTablica()[indeks];
		if (tablica->getTablica()[lewyPotomekIndeks] > max) {
			max = tablica->getTablica()[lewyPotomekIndeks];
			
			//najwi�kszy prawy
			if (tablica->getTablica()[prawyPotomekIndeks] > max) {
				tablica->zamien(prawyPotomekIndeks, indeks);
				naprawKopiecDol(prawyPotomekIndeks);
				return;
			}

			//najwi�kszy lewy
			tablica->zamien(lewyPotomekIndeks, indeks);
			naprawKopiecDol(lewyPotomekIndeks);
			return;
		}

		//najwi�kszy prawy
		if (tablica->getTablica()[prawyPotomekIndeks] > max) {
			tablica->zamien(prawyPotomekIndeks, indeks);
			naprawKopiecDol(prawyPotomekIndeks);
			return;
		}
	} 
	//nie ma potomk�w
	else {
		//nic nie r�b
		//koniec rekurencji
		return;
	}
}









