#include "Dane.h"
#include <fstream>
#include <iostream>
#include "Menu.h"

using namespace std;

/*
Klasa odpowiada za wczytywanie danych z pliku tekstowego.
Dane s¹ wczytywane do tablicy dynamicznej
*/

Dane::Dane(TablicaDynamiczna* tablica) {
	liczbaOpcji = 4;
	
	this->sciezka = "dane.txt";
	this->tablica = tablica;
	

}

void Dane::menu() {
	string tablica[] = { "wczytaj dane", "ustaw œcie¿kê", "wyœwietl œcie¿kê", "kasuj dane" };
	Menu menu = Menu(liczbaOpcji, tablica, "Dane");
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			try {
				wczytaj();
				cout << "Dane wczytano pomyœlnie" << endl;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		case 1:
			ustawSciezke();
			cout << "Œcie¿ka ustawiona" << endl;
			break;

		case 2:
			cout << sciezka << endl;
			break;
		case 3:
			delete this->tablica;
			this->tablica = new TablicaDynamiczna();
			cout << "Dane skasowano pomyœlnie" << endl;
			break;
		} 
	}
}


void Dane::ustawSciezke() {
	cout << "WprowadŸ œcie¿kê: ";
	cin >> sciezka;
}

/*
Wczytywanie danych z pliku
Zwraca dane w tablicy dynamicznej
*/
void Dane::wczytaj() {
	ifstream plik;
	plik.open(sciezka);
	int rozmiar = 0;
	int* tablica;
	int liczba;
	if (plik.is_open()) {
		//wczytywanie rozmiaru
		plik >> rozmiar;
		if (plik.fail())
			throw exception("B³¹d wczytania rozmiaru danych z pliku");
		else {
			//alokacja pamiêci na dane
			tablica = new int[rozmiar];

			//wczytywanie kolejnych wartoœci
			for (int i = 0; i < rozmiar; i++) {
				plik >> liczba;
				if (plik.fail()) {
					throw exception("B³¹d wczytania wartoœci z pliku");
				}
				else {
					tablica[i] = liczba;
				}
			}
		}
		this->tablica = new TablicaDynamiczna(rozmiar, tablica);
		plik.close();
	}
	else
		throw exception("B³¹d otwartcia pliku");
	
}


TablicaDynamiczna* Dane::getTablica() {
	return tablica;
}



