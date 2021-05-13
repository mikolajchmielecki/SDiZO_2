#include "GrafLista.h"

GrafLista::GrafLista(int liczbaKrawedzi, int liczbaWierzcholkow, int wierzcholekStartowy, int wierzcholekKoncowy, bool czySkierowany) {
	this->liczbaKrawedzi = liczbaKrawedzi;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = wierzcholekStartowy;
	this->wierzcholekKoncowy = wierzcholekKoncowy;
	tablicaList = new Tablica<Lista<Sasiad*>*>(liczbaWierzcholkow);
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		tablicaList->tablica[i] = new Lista<Sasiad*>;
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
	string wynik = "Lista s¹siedztwa:\n[wierzcho³ek startowy] -> [s¹siad] ([waga]) -> ... -> STOP\n\n";
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
	sprawdzKrawedz();
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


