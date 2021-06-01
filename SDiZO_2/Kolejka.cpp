#include "Kolejka.h"

Kolejka::Kolejka(TrybPrzeszukiwania tryb) {
	this->tryb = tryb;
	lista = new Lista<Krawedz*>();

}

Kolejka::~Kolejka() {
	while (lista->getRozmiar() > 0) {
		delete lista->getElement(0);
		lista->usunPoczatek();
	}

	delete lista;
}

void Kolejka::push(Krawedz* wierzcholek) {
	if (tryb == TrybPrzeszukiwania::BFS) {
		lista->dodajKoniec(wierzcholek);
	}
	if (tryb == TrybPrzeszukiwania::DFS) {
		lista->dodajPoczatek(wierzcholek);
	}
}

Krawedz* Kolejka::pop() {
	Krawedz* wierzcholek = lista->getElement(0);
	lista->usunPoczatek();
	return wierzcholek;
}

bool Kolejka::czyPusta() {
	return lista->getRozmiar() == 0;
}
