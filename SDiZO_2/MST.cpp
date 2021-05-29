#include "MST.h"


/*
Metoda wykorzytywana do sortowania krawedzi wynikowych MST
Ustawia krawedzie od najmniejszego pocz¹tku
Je¿eli pocz¹tke jest ten sam to decyduje wartoœæ koñca
*/
bool porownajKrawedzie(Krawedz* krawedz1, Krawedz* krawedz2) {
	if (krawedz1->start < krawedz2->start) {
		return true;
	}
	if (krawedz1->start == krawedz2->start) {
		return krawedz1->koniec < krawedz2->koniec;
	}
	return false;

}

string MST::getWynik() {

	int sumaWag = 0;
	for (int i = 0; i < krawedzieMST->getRozmiar(); i++) {
		sumaWag += krawedzieMST->tablica[i]->waga;
	}

	// sprawdzenie czy graf jest niespójny
	// korzystam z zale¿noœci ¿e dla drzewa V = E+1
	if (graf->liczbaWierzcholkow != krawedzieMST->getRozmiar() + 1) {
		throw exception("[ERROR] Graf jest niespójny");
	}

	krawedzieMST->sortuj(&porownajKrawedzie);

	string wynik = " Edge\t\tWeight\n";

	for (int i = 0; i < krawedzieMST->getRozmiar(); i++) {
		wynik += " ";
		wynik += krawedzieMST->tablica[i]->toString();
		wynik += "\n";
	}

	wynik += "MST = ";
	wynik += to_string(sumaWag);
	wynik += "\n";

	

	return wynik;
}
