#include "Krawedz.h"

Krawedz::Krawedz(int start, int koniec, int waga, int przeplyw) {
	this->start = start;
	this->koniec = koniec;
	this->waga = waga;
	this->przeplyw = przeplyw;
}

string Krawedz::toString() {
	string wynik = "(";
	wynik += to_string(start);
	wynik += ",";
	wynik += to_string(koniec);
	wynik += ")\t\t";
	wynik += to_string(waga);
	return wynik;
}
