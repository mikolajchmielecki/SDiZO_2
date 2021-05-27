#include "GrafLista.h"

GrafLista::GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany) {
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	this->czySkierowany = czySkierowany;
	tablicaList = new Tablica<Lista<Sasiad*>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		tablicaList->tablica[i] = new Lista<Sasiad*>;
	}

	iteratorRzad = 0;
	iteratorKolumna = nullptr;
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
*/
void GrafLista::dodajKrawedz(int start, int koniec, int waga) {
	sprawdzKrawedz(start, koniec, waga);
	Sasiad* sasiad = new Sasiad;
	sasiad->numerWierzcholka = koniec;
	sasiad->waga = waga;
	tablicaList->tablica[start]->dodajPoczatek(sasiad);

	
	if (!czySkierowany) {
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
Krawedz* GrafLista::nastepnaKrawedz() {
	int maksymalnyRzad = liczbaWierzcholkow;

	// bierzemy tylko pod uwage pierwsz¹ po³owê wierzcho³ków, gdy¿ krawedzie s¹ zapisane podwójnie
	if (czySkierowany == false) {
		maksymalnyRzad = (liczbaWierzcholkow + 1)/ 2;
	}

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

void GrafLista::inicjalizujIteratorSasiadow(int wierzcholek)
{
}

Krawedz* GrafLista::nastepnySasiad()
{
	return nullptr;
}


