#include "GrafLista.h"


/*
Parametr czyDuplikaty jest potrzebny dla algorytmów MST
Algorytm Prima wczytuje podwójnie krawedzie
Algorytm Kruskala wczytuje pojedyczno krawedzie
*/
GrafLista::GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czyDuplikaty, TypAlgorytmu typAlgorytmu) {
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
	if (typAlgorytmu == TypAlgorytmu::MST) {
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
Przektsza³ca reprezentacjê macierzow¹ na string w celu wyswietltenia
*/
string GrafLista::toString() {
	string wynik = "Lista s¹siedztwa:\n";

	if (czySkierowany) {
		wynik += "[wierzcho³ek startowy]";
	}
	else {
		wynik += "(graf nieskierowany) [wierzcho³ek]";
	}
	wynik += " -> [s¹siad] ([waga]) -> ... -> STOP\n\n";

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
Wstawia danego s¹siada na pocz¹tek listy s¹siedztwa.
Je¿eli graf jest nieskierowany i oczekujemy duplikatów to dodajemy krawedzie podwójnie
*/
void GrafLista::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz(start, koniec, waga);
	


	Sasiad* sasiad = new Sasiad;
	sasiad->numerWierzcholka = koniec;
	sasiad->waga = waga;
	tablicaList->tablica[start]->dodajPoczatek(sasiad);

	
	if (!czySkierowany && czyDuplikaty) {
		Sasiad* sasiad = new Sasiad;
		sasiad->numerWierzcholka = start;
		sasiad->waga = waga;
		tablicaList->tablica[koniec]->dodajPoczatek(sasiad);
	}
	
}

void GrafLista::inicjalizujIteratorKrawedzi() {
	iteratorRzad = 0;

	// pierwszy sasiad wierzcho³ka 0
	iteratorKolumna = tablicaList->tablica[0]->glowa;
}

/*
Zwracanie nastêpnej krawêdzi z kolejki
*/

// TODO: do poprawy dla grafu nieskierowanego
Krawedz* GrafLista::nastepnaKrawedz() {
	int maksymalnyRzad = liczbaWierzcholkow;

	if (iteratorRzad >= maksymalnyRzad) {
		return nullptr;
	}

	// iteruje po ka¿dym wierzcho³ku
	for (; iteratorRzad < maksymalnyRzad; iteratorRzad++) {
		if (iteratorKolumna != nullptr) {
			ElementListy<Sasiad*>* iteratorKolumnaTemp = iteratorKolumna;
			iteratorKolumna = iteratorKolumna->nastepny;
			return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga);
		}
		// przejscie do nastêpnej listy
		else {
			if (iteratorRzad < maksymalnyRzad-1) {
				iteratorKolumna = tablicaList->tablica[iteratorRzad + 1]->glowa;
			}
		}
	}
	return nullptr;
}

void GrafLista::inicjalizujIteratorSasiadow(int wierzcholek) {
	iteratorKolumna = tablicaList->tablica[wierzcholek]->glowa;
}

/*
Zwraca nastêpnego s¹siada z listy
*/
Krawedz* GrafLista::nastepnySasiad() {
	if (iteratorKolumna != nullptr) {
		ElementListy<Sasiad*>* iteratorKolumnaTemp = iteratorKolumna;
		iteratorKolumna = iteratorKolumna->nastepny;
		return new Krawedz(iteratorRzad, iteratorKolumnaTemp->element->numerWierzcholka, iteratorKolumnaTemp->element->waga);
	}
	return nullptr;
}


