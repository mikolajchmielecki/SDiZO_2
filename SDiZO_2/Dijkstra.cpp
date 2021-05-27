#include "Dijkstra.h"

Dijkstra::Dijkstra(IGraf* graf) {
	this->graf = graf;
}

Dijkstra::~Dijkstra() {
}

void Dijkstra::uruchom() {
	// tablica odleg³oœci oraz poprzedników
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
	}

	// inicjalizacja wierzcho³ka pocz¹tkowego
	wierzcholki->tablica[0]->klucz = 0;
}
