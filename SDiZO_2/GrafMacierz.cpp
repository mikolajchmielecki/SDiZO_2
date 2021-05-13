#include "GrafMacierz.h"

GrafMacierz::GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany) {
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	macierz = new Tablica<Tablica<int>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierz->tablica[i] = new Tablica<int>(liczbaWierzcholkow);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			macierz->tablica[i]->tablica[j] = INT_MAX;
		}
	}
}

/*
Zwalnia pami�� rezerwowan� przez macierz
*/
GrafMacierz::~GrafMacierz() {
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		delete macierz->tablica[i];
	}
	delete macierz;
}



/*
Dodaje krawed� do macierzy
W przypadku kiedy graf jest nieskierowany to dodajemy kraw�d� w dw�ch miejscach
*/
void GrafMacierz::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz();
	macierz->tablica[start]->tablica[koniec] = waga;
	if (!czySkierowany) {
		macierz->tablica[koniec]->tablica[start] = waga;
	}
}

/*
Przektsza�ca reprezentacj� macierzow� na string w celu wyswietltenia
*/
string GrafMacierz::toString() {
	string wynik = "Macierz s�siedztwa: (S - wierzcho�ek startowy, K - wierzcho�ek ko�cowy)\n\n";
	int szerokoscKomorki = to_string(INT_MIN).length();

	// nag��wek
	string opis = "S \\ K";
	wynik += wyrownajString(opis, szerokoscKomorki);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		wynik += "|" + wyrownajString(to_string(i), szerokoscKomorki);
	}
	wynik += "\n";
	

	// zawarto��
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		// pozioma linia
		wynik += powielZnak('�', szerokoscKomorki * (liczbaWierzcholkow + 1) + liczbaWierzcholkow) + "\n";

		// numer wiersza
		wynik += wyrownajString(to_string(i), szerokoscKomorki);

		// kolejne kom�rki - wagi
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			string komorka = "";
			if (macierz->tablica[i]->tablica[j] != INT_MAX) {
				komorka = to_string(macierz->tablica[i]->tablica[j]);
			}
			wynik += "|" + wyrownajString(komorka, szerokoscKomorki);
		}
		wynik += "\n";
	}

	return wynik;
}


