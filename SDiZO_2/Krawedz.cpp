#include "Krawedz.h"

Krawedz::Krawedz(int start, int koniec, int waga) {
	this->start = start;
	this->koniec = koniec;
	this->waga = waga;
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
