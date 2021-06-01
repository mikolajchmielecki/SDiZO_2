#include "GrafMacierz.h"

GrafMacierz::GrafMacierz(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypAlgorytmu typAlgorytmu) {
	
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	this->czyDuplikaty = czyDuplikaty;
	macierz = new Tablica<Tablica<int>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierz->tablica[i] = new Tablica<int>(liczbaWierzcholkow);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			macierz->tablica[i]->tablica[j] = INT_MAX;
		}
	}


	iteratorKolumna = 0;
	iteratorRzad = 0;
	iteratorSasiad = 0;
	iteratorWierzcholek = 0;

	this->typAlgorytmu = typAlgorytmu;
	this->czySkierowany = true;
	if (typAlgorytmu == TypAlgorytmu::MST) {
		this->czySkierowany = false;
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

	if (typAlgorytmu == TypAlgorytmu::MF) {
		for (int i = 0; i < liczbaWierzcholkow; i++) {
			delete macierzPrzeplywow->tablica[i];
		}
		delete macierzPrzeplywow;
	}
}



/*
Dodaje krawedŸ do macierzy
W przypadku kiedy graf jest nieskierowany oraz oczekujemy duplikatów to wypa³eniamy podwójnie
W przypadku keidy graf jest nieskierowany oraz nie oczekujemy duplikatów to wype³niany lewy dolny trójk¹

*/
void GrafMacierz::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz(start, koniec, waga);
	
	if (!czySkierowany) {
		if (start < koniec) {
			swap(start, koniec);
		}
	}
	if (!czySkierowany && czyDuplikaty) {
		if (macierz->tablica[koniec]->tablica[start] != INT_MAX) {
			throw exception("[ERROR] Wyst¹pi³o redefiniowanie krawedzi");
		}
		macierz->tablica[koniec]->tablica[start] = waga;
	}
	if (macierz->tablica[start]->tablica[koniec] != INT_MAX) {
		throw exception("[ERROR] Wyst¹pi³o redefiniowanie krawedzi");
	}
	macierz->tablica[start]->tablica[koniec] = waga;
	
}

/*
Ustawia punkt pocz¹tku na lewy górny róg macierzy
*/
void GrafMacierz::inicjalizujIteratorKrawedzi() {
	iteratorKolumna = 0;
	iteratorRzad = 0;
}

/*
Poszukuje kolejnej krawêdzi, której waga jest ró¿na od MAX_INT
*/
Krawedz* GrafMacierz::nastepnaKrawedz() {
	
	// sprawdzenei czy w poprzednim wywo³aniu nie wyszliœmy poza zakres
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

	// wyjœcie poza zakres
	if (iteratorRzad >= liczbaWierzcholkow) {
		return nullptr;
	}

	for (; iteratorRzad < liczbaWierzcholkow; iteratorRzad++) {
		for (; iteratorKolumna < liczbaWierzcholkow; iteratorKolumna++) {
			
			// dla grafu nieskierowanego brany jest pod uwage tylko lewy dolny trójk¹t
			if (czySkierowany == false) {
				if (iteratorKolumna >= iteratorRzad) {
					break;
				}
			}
			
			// je¿eli dana krawedŸ istnieje do j¹ zwracamy
			int waga = macierz->tablica[iteratorRzad]->tablica[iteratorKolumna];
			if (waga != INT_MAX) {

				// przejœcie do kolejnej komórki
				iteratorKolumna++;
				if (typAlgorytmu == TypAlgorytmu::MF) {
					int przeplyw = macierzPrzeplywow->tablica[iteratorRzad]->tablica[iteratorKolumna - 1];
					return new Krawedz(iteratorRzad, iteratorKolumna - 1, waga, przeplyw);
				}

				return new Krawedz(iteratorRzad, iteratorKolumna-1, waga);
			}
		}
		iteratorKolumna = 0;
	}
	return nullptr;
}

void GrafMacierz::inicjalizujIteratorSasiadow(int wierzcholek) {
	iteratorWierzcholek = wierzcholek;
	iteratorSasiad = 0;
}

Krawedz* GrafMacierz::nastepnySasiad() {
	// sprawdzenie czy w poprzednim wywo³aniu nie wyszliœmy poza zakres
	if (iteratorSasiad >= liczbaWierzcholkow && czyDuplikaty) {
		return nullptr;
	}

	// sprawdzenie czy w poprzednim wywo³aniu nie wyszliœmy poza lewy dolny trójk¹t
	if (iteratorSasiad >= iteratorWierzcholek && !czyDuplikaty) {
		return nullptr;
	}




	for (; iteratorSasiad < liczbaWierzcholkow; iteratorSasiad++) {

		// je¿eli dana krawedŸ istnieje do j¹ zwracamy
		int waga = macierz->tablica[iteratorWierzcholek]->tablica[iteratorSasiad];
		if (waga != INT_MAX) {

			// przejœcie do kolejnej komórki
			iteratorSasiad++;

			if (typAlgorytmu == TypAlgorytmu::MF) {
				int przeplyw = macierzPrzeplywow->tablica[iteratorWierzcholek]->tablica[iteratorSasiad-1];
				return new Krawedz(iteratorWierzcholek, iteratorSasiad - 1, waga, przeplyw);
			}
			else {
				return new Krawedz(iteratorWierzcholek, iteratorSasiad - 1, waga);
			}
			
		}
	}

	return nullptr;
}

/*
Je¿eli przepustowosc = inf to uznajemy ze nie mamy krawedzi
Tworzymy symetryczne krawedzie i przepustowosciach 0
Inicjalizujemy wszystkie przeplywy na 0
*/
void GrafMacierz::inicjalizujPrzeplywy() {
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			int przepustowosc = macierz->tablica[i]->tablica[j];
			if (przepustowosc != INT_MAX && przepustowosc != 0) {
				int przepustowosc1 = macierz->tablica[j]->tablica[i];
				if (przepustowosc1 == INT_MAX) {
					macierz->tablica[j]->tablica[i] = 0;
					liczbaKrawedzi++;
				}
			}
		}
	}

	macierzPrzeplywow = new Tablica<Tablica<int>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierzPrzeplywow->tablica[i] = new Tablica<int>(liczbaWierzcholkow);
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			macierzPrzeplywow->tablica[i]->tablica[j] = 0;
		}
	}
}

void GrafMacierz::zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu) {
	macierzPrzeplywow->tablica[start]->tablica[koniec] += zmianaPrzeplywu;
}

/*
Przektsza³ca reprezentacjê macierzow¹ na string w celu wyswietltenia
*/
string GrafMacierz::toString() {
	string wynik = "Macierz s¹siedztwa : ";
	if (czySkierowany) {
		wynik += "(S - wierzcho³ek startowy, K - wierzcho³ek koñcowy)\n\n";
	}
	else {
		wynik += "(graf nieskierowany)\n\n";
	}
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


