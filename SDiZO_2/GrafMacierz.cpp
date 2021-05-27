#include "GrafMacierz.h"

GrafMacierz::GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany) {
	
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	this->czySkierowany = czySkierowany;
	macierz = new Tablica<Tablica<int>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierz->tablica[i] = new Tablica<int>(liczbaWierzcholkow);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			macierz->tablica[i]->tablica[j] = INT_MAX;
		}
	}
	iteratorKolumna = 0;
	iteratorRzad = 0;
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
W przypadku kiedy graf jest nieskierowany to wype�aniony jest tylko lewy dolny trj�jkat macierzy

*/
void GrafMacierz::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz(start, koniec, waga);
	macierz->tablica[start]->tablica[koniec] = waga;
	/*
	if (!czySkierowany) {
		macierz->tablica[koniec]->tablica[start] = waga;
	}
	*/
}

/*
Ustawia punkt pocz�tku na lewy g�rny r�g macierzy
*/
void GrafMacierz::inicjalizujIteratorKrawedzi() {
	iteratorKolumna = 0;
	iteratorRzad = 0;
}

/*
Poszukuje kolejnej kraw�dzi, kt�rej waga jest r�na od MAX_INT
*/
Krawedz* GrafMacierz::nastepnaKrawedz() {
	
	// sprawdzenei czy w poprzednim wywo�aniu nie wyszli�my poza zakres
	if (czySkierowany == false) {
		if (iteratorKolumna >= iteratorRzad) {
			iteratorKolumna = 0;
			iteratorRzad++;
		}
	}
	// skierowany
	else {
		if (iteratorKolumna >= liczbaWierzcholkow) {
			iteratorKolumna = 0;
			iteratorRzad++;
		}
	}

	// wyj�cie poza zakres
	if (iteratorRzad >= liczbaWierzcholkow) {
		return nullptr;
	}

	for (; iteratorRzad < liczbaWierzcholkow; iteratorRzad++) {
		for (; iteratorKolumna < liczbaWierzcholkow; iteratorKolumna++) {
			
			// dla grafu nieskierowanego brany jest pod uwage tylko lewy dolny tr�jk�t
			if (czySkierowany == false) {
				if (iteratorKolumna >= iteratorRzad) {
					break;
				}
			}
			
			// je�eli dana krawed� istnieje do j� zwracamy
			int waga = macierz->tablica[iteratorRzad]->tablica[iteratorKolumna];
			if (waga != INT_MAX) {

				// przej�cie do kolejnej kom�rki
				iteratorKolumna++;

				return new Krawedz(iteratorRzad, iteratorKolumna-1, waga);
			}
		}
		iteratorKolumna = 0;
	}
	return nullptr;
}

void GrafMacierz::inicjalizujIteratorSasiadow(int wierzcholek)
{
}

Krawedz* GrafMacierz::nastepnySasiad()
{
	return nullptr;
}

/*
Przektsza�ca reprezentacj� macierzow� na string w celu wyswietltenia
*/
string GrafMacierz::toString() {
	string wynik = "Macierz s�siedztwa : ";
	if (czySkierowany) {
		wynik += "(S - wierzcho�ek startowy, K - wierzcho�ek ko�cowy)\n\n";
	}
	else {
		wynik += "(graf nieskierowany)\n\n";
	}
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


