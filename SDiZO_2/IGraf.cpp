#include "IGraf.h"

void IGraf::sprawdzKrawedz(int start, int koniec, int waga) {
	if (start < 0 || koniec < 0 || start > liczbaWierzcholkow - 1 || koniec > liczbaWierzcholkow - 1 || waga == INT_MAX) {
		throw exception("[ERROR] B��d wczytania kraw�dzi");
	}

	if (typAlgorytmu == TypProblemu::MF && waga <= 0) {
		throw exception("[ERROR] Niedodatni przep�yw");
	}
}

/*
Tworzy stringa z liczby o sta�ej szeroko�ci i dodaje zako�czenia |
*/
string IGraf::wyrownajString(string liczbaString, int szerokosc) {
	int rozmiarWypelnienia = szerokosc - liczbaString.length();
	string wypelnienie = powielZnak(' ', rozmiarWypelnienia);
	return wypelnienie + liczbaString;
}

string IGraf::powielZnak(char znak, int powtorzenia) {
	string wynik = "";
	for (int i = 0; i < powtorzenia; i++) {
		wynik += znak;
	}
	return wynik;
}

IGraf::~IGraf()
{
}
