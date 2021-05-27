#include "Dijkstra.h"

Dijkstra::Dijkstra(IGraf* graf) {
	this->graf = graf;
}

Dijkstra::~Dijkstra() {
}

void Dijkstra::uruchom() {
	// tablica odleg�o�ci oraz poprzednik�w
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
	}

	// inicjalizacja wierzcho�ka pocz�tkowego
	wierzcholki->tablica[0]->klucz = 0;
}
