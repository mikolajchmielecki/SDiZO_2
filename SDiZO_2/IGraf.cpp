#include "IGraf.h"

void IGraf::sprawdzKrawedz() {

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
