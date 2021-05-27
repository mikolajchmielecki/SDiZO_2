#include "Dijkstra.h"

Dijkstra::Dijkstra(IGraf* graf) {
	this->graf = graf;
}

Dijkstra::~Dijkstra() {
}

void Dijkstra::uruchom() {
	// tablica odległości oraz poprzedników
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);

	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura();
	}

	// inicjalizacja wierzchołka początkowego
	wierzcholki->tablica[0]->klucz = 0;
}
