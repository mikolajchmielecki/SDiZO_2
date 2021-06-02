#include "Kruskal.h"

bool czyMniejszaWaga(Krawedz* krawedz1, Krawedz* krawedz2) {
	return krawedz1->waga < krawedz2->waga;
}


Kruskal::Kruskal() {
	
}

Kruskal::~Kruskal() {
	if (!zwolniony) {
		for (int i = 0; i < krawedzie->getRozmiar(); i++) {
			Krawedz* krawedz = krawedzie->tablica[i];
			if (krawedz != nullptr) {
				delete krawedz;
			}
		}
		delete krawedzie;
		delete krawedzieMST;
	}
}

void Kruskal::uruchom() {
	// rezerwacja miejsca na krawedzie MST
	krawedzieMST = new Tablica<Krawedz*>(graf->liczbaWierzcholkow - 1);

	krawedzie = new Tablica<Krawedz*>(graf->liczbaKrawedzi);

	graf->inicjalizujIteratorKrawedzi();
	Krawedz* krawedz = graf->nastepnaKrawedz();

	int iteratorKrawedzie = 0;
	// tworzenie tablicy krawedzi
	while (krawedz != nullptr) {
		krawedzie->tablica[iteratorKrawedzie] = krawedz;
		iteratorKrawedzie++;
		krawedz = graf->nastepnaKrawedz();
	}

	krawedzie->sortuj(&czyMniejszaWaga);

	// tworzenie zbior�w
	Tablica<Zbior*>* zbiory = new Tablica<Zbior*>(graf->liczbaWierzcholkow);
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		zbiory->tablica[i] = new Zbior(i);
	}


	int iteratorKrawedzieMST = 0;
	// sprawdzanie ka�dej krawedzi pocz�wszy od najmniejszych wag
	for (int i = 0; i < krawedzie->getRozmiar(); i++) {
		Krawedz* krawedz = krawedzie->tablica[i];
		Zbior* zbior1 = zbiory->tablica[krawedz->start]->getIdentyfikator();
		Zbior* zbior2 = zbiory->tablica[krawedz->koniec]->getIdentyfikator();
		if (zbior1 != zbior2) {

			krawedzieMST->tablica[iteratorKrawedzieMST] = krawedz;
			Zbior::polaczZbiory(zbior1, zbior2);
			iteratorKrawedzieMST++;
		}
		if (iteratorKrawedzieMST == graf->liczbaWierzcholkow - 1) {
			break;
		}
	}


	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		delete zbiory->tablica[i];
	}
	delete zbiory;

}

void Kruskal::inicjalizuj(IGraf* graf) {
	this->graf = graf;
	zwolniony = false;
}

void Kruskal::zwolnij() {
	zwolniony = true;
	for (int i = 0; i < krawedzie->getRozmiar(); i++) {
		Krawedz* krawedz = krawedzie->tablica[i];
		if (krawedz != nullptr) {
			delete krawedz;
		}
	}
	delete krawedzie;
	delete krawedzieMST;
}

string Kruskal::getNazwa()
{
	return "Kruskal";
}
