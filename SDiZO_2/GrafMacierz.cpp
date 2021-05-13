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
Zwalnia pamiêæ rezerwowan¹ przez macierz
*/
GrafMacierz::~GrafMacierz() {
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		delete macierz->tablica[i];
	}
	delete macierz;
}



/*
Dodaje krawedŸ do macierzy
W przypadku kiedy graf jest nieskierowany to dodajemy krawêdŸ w dwóch miejscach
*/
void GrafMacierz::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz();
	macierz->tablica[start]->tablica[koniec] = waga;
	if (!czySkierowany) {
		macierz->tablica[koniec]->tablica[start] = waga;
	}
}

/*
Przektsza³ca reprezentacjê macierzow¹ na string w celu wyswietltenia
*/
string GrafMacierz::toString() {
	string wynik = "Macierz s¹siedztwa: (S - wierzcho³ek startowy, K - wierzcho³ek koñcowy)\n\n";
	int szerokoscKomorki = to_string(INT_MIN).length();

	// nag³ówek
	string opis = "S \\ K";
	wynik += wyrownajString(opis, szerokoscKomorki);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		wynik += "|" + wyrownajString(to_string(i), szerokoscKomorki);
	}
	wynik += "\n";
	

	// zawartoœæ
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		// pozioma linia
		wynik += powielZnak('–', szerokoscKomorki * (liczbaWierzcholkow + 1) + liczbaWierzcholkow) + "\n";

		// numer wiersza
		wynik += wyrownajString(to_string(i), szerokoscKomorki);

		// kolejne komórki - wagi
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


