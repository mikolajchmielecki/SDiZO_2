#include "Menu.h"
#include <iostream>

using namespace std;

/*
Klasa odpowiada za wy�wietlanie menu i zwracanie nr wybranej funkcji
*/


Menu::Menu(int liczbaOpcji, string* opcje, string nazwa) {
	uruchomione = true;
	menuString.append("\n"+nazwa+"\n");
	menuString.append("q - wyjd�\n");
	this->liczbaOpcji = liczbaOpcji;
	for (int i = 0; i < liczbaOpcji; i++) {
		menuString.append( "" + to_string(i) + " - ");
		menuString.append(opcje[i]);
		menuString.append("\n");
	}
	menuString.append("\n");
}


/*
q - wyj�cie
kolejne numery - indeksy funkcji w tablicy "opcje"
*/
int Menu::wyswietl() {
	cout << menuString;
	cout << "Wprowad�: ";
	string wejscie = "";
	cin >> wejscie;
	int wejscieLiczba = -1;
	if (wejscie != "q") {
		try {
			wejscieLiczba = stoi(wejscie);
		}
		catch (exception) {
			cout << "Nie wprowadzono liczby\n";
			return wejscieLiczba;
		}

		if (wejscieLiczba < 0 || wejscieLiczba >= liczbaOpcji) {
			cout << "Wprowadzono liczb� poza zakresem\n";
			return wejscieLiczba;
		}
	}
	else {
		uruchomione = false;
	}
	return wejscieLiczba;
}

bool Menu::czyUruchomione() {
	return uruchomione;
}


