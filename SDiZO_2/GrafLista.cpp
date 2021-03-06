#include "GrafLista.h"




/*
Parametr czyDuplikaty jest potrzebny dla algorytm?w MST
Algorytm Prima wczytuje podw?jnie krawedzie
Algorytm Kruskala wczytuje pojedyczno krawedzie
*/
GrafLista::GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypProblemu typAlgorytmu) {
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	this->czyDuplikaty = czyDuplikaty;
	tablicaList = new Tablica<Lista<Sasiad*>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		tablicaList->tablica[i] = new Lista<Sasiad*>;
	}

	iteratorRzad = 0;
	iteratorKolumna = nullptr;
	this->typAlgorytmu = typAlgorytmu;
	this->czySkierowany = true;
	if (typAlgorytmu == TypProblemu::MST) {
		this->czySkierowany = false;
	}
}

GrafLista::~GrafLista() {
	for (int i = 0; i < tablicaList->getRozmiar(); i++) {
		Lista<Sasiad*>* lista = tablicaList->tablica[i];
		ElementListy<Sasiad*>* elementListy = lista->getIterator();
		for (int j = 0; j < lista->getRozmiar(); j++) {
			delete elementListy->element;
			elementListy = elementListy->nastepny;
		}
		delete lista;
	}
	delete tablicaList;
}

/*
Przektsza?ca reprezentacj? macierzow? na string w celu wyswietltenia
*/
string GrafLista::toString() {
	string wynik = "Lista s?siedztwa:\n";

	if (czySkierowany) {
		wynik += "[wierzcho?ek startowy]";
	}
	else {
		wynik += "(graf nieskierowany) [wierzcho?ek]";
	}
	wynik += " -> [s?siad] ([waga]) -> ... -> STOP\n\n";

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		wynik += to_string(i) + " -> ";
		Lista<Sasiad*>* lista = tablicaList->tablica[i];
		
		auto elementListy = lista->getIterator();
		for (int j = 0; j < lista->getRozmiar(); j++) {
			wynik += to_string(elementListy->element->numerWierzcholka) + " (" + to_string(elementListy->element->waga) + ") -> ";
			elementListy = elementListy->nastepny;
		}

		wynik += "STOP\n";
	}
	return wynik;
}

/*
Dodaje krawedz do listy sasiedztwa.
Wstawia danego s?siada na pocz?tek listy s?siedztwa.
Je?eli graf jest nieskierowany i oczekujemy duplikat?w to dodajemy krawedzie podw?jnie
*/
void GrafLista::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz(start, koniec, waga);
	
	Sasiad* sasiad = new Sasiad;
	sasiad->numerWierzcholka = koniec;
	sasiad->waga = waga;
	sasiad->przeplyw = 0;

	if (czySasiedzi(start, koniec)) {
		throw exception("[ERROR] Wyst?pi?o redefiniowanie krawedzi");
	}
	if (!czySkierowany && czySasiedzi(koniec, start)) {
		throw exception("[ERROR] Wyst?pi?o redefiniowanie krawedzi");
	}
	tablicaList->tablica[start]->dodajPoczatek(sasiad);

	
	if (!czySkierowany && czyDuplikaty) {
		Sasiad* sasiad = new Sasiad;
		sasiad->numerWierzcholka = start;
		sasiad->waga = waga;
		sasiad->przeplyw = 0;
		if (czySasiedzi(koniec, start)) {
			throw exception("[ERROR] Wyst?pi?o redefiniowanie krawedzi");
		}
		tablicaList->tablica[koniec]->dodajPoczatek(sasiad);
	}
	
}

void GrafLista::inicjalizujIteratorKrawedzi() {
	iteratorRzad = 0;

	// pierwszy sasiad wierzcho?ka 0
	iteratorKolumna = tablicaList->tablica[0]->glowa;
}

/*
Zwracanie nast?pnej kraw?dzi z kolejki
*/

// TODO: do poprawy dla grafu nieskierowanego
Krawedz* GrafLista::nastepnaKrawedz() {
	int maksymalnyRzad = liczbaWierzcholkow;

	if (iteratorRzad >= maksymalnyRzad) {
		return nullptr;
	}

	// iteruje po ka?dym wierzcho?ku
	for (; iteratorRzad < maksymalnyRzad; iteratorRzad++) {
		if (iteratorKolumna != nullptr) {
			ElementListy<Sasiad*>* iteratorKolumnaTemp = iteratorKolumna;
			iteratorKolumna = iteratorKolumna->nastepny;
			if (typAlgorytmu == TypProblemu::MF) {
				return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga, iteratorKolumnaTemp->element->przeplyw);
			}

			return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga);
		}
		// przejscie do nast?pnej listy
		else {
			if (iteratorRzad < maksymalnyRzad-1) {
				iteratorKolumna = tablicaList->tablica[iteratorRzad + 1]->glowa;
			}
		}
	}
	return nullptr;
}

string GrafLista::getNazwa() {
	return "reprezentacja listowa";
}

void GrafLista::inicjalizujIteratorSasiadow(int wierzcholek) {
	iteratorRzad = wierzcholek;
	iteratorKolumna = tablicaList->tablica[wierzcholek]->glowa;
}

/*
Zwraca nast?pnego s?siada z listy
*/
Krawedz* GrafLista::nastepnySasiad() {
	if (iteratorKolumna != nullptr) {
		ElementListy<Sasiad*>* iteratorKolumnaTemp = iteratorKolumna;
		iteratorKolumna = iteratorKolumna->nastepny;

		if (typAlgorytmu == TypProblemu::MF) {
			return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga, iteratorKolumnaTemp->element->przeplyw);
		}
		else {
			return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga);
		}
	}
	return nullptr;
}

void GrafLista::inicjalizujPrzeplywy() {
	// dla ka?dego wierzcholka
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		inicjalizujIteratorSasiadow(i);
		Krawedz* krawedz = nastepnySasiad();
		// dla ka?dego sasiada i
		while (krawedz != nullptr) {

			// dodanie krawedzi zwrotnych jesli nie istnieja
			int sasiad_id = krawedz->koniec;
			if (czySasiedzi(sasiad_id, i) == false) {
				Sasiad* sasiad = new Sasiad;
				sasiad->przeplyw = 0;
				sasiad->numerWierzcholka = i;
				sasiad->waga = 0;
				tablicaList->tablica[sasiad_id]->dodajPoczatek(sasiad);
				liczbaKrawedzi++;
			}


			delete krawedz;
			krawedz = nastepnySasiad();
		}
	}

}

void GrafLista::zmienPrzeplyw(int start, int koniec, int zmianaPrzeplywu) {
	ElementListy<Sasiad*>* iteratorKolumna = tablicaList->tablica[start]->glowa;
	while (iteratorKolumna != nullptr) {
		if (iteratorKolumna->element->numerWierzcholka == koniec) {
			iteratorKolumna->element->przeplyw += zmianaPrzeplywu;
			return;
		}
		iteratorKolumna = iteratorKolumna->nastepny;
	}
	throw exception("[ERROR] Brak wierzcho?ka na li?cie s?siad?w");
}

bool GrafLista::czySasiedzi(int start, int koniec) {
	ElementListy<Sasiad*>* iteratorKolumna = tablicaList->tablica[start]->glowa;
	while (iteratorKolumna != nullptr) {
		if (iteratorKolumna->element->numerWierzcholka == koniec) {
			return true;
		}
		iteratorKolumna = iteratorKolumna->nastepny;
	}
	return false;
}


