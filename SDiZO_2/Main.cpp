#include<iostream>
#include<locale.h>
#include<string>
#include "Menu.h"
#include "Typy.h"
#include "IGraf.h"
#include "GrafMacierz.h"
#include "GrafLista.h"
#include "MySTL.h"
#include "Dane.h"
#include "BellmanFord.h"


// SP - shortest path
// MST - minimal spaning tree
// MF - max flow

// Teksty wyœwietlane w menu

int liczbaOpcji = 4;
string opcje[] = { "Najkrótsza œcie¿ka", "Minimalne drzewo rozpinaj¹ce", "Maksymalny przep³yw", "Dane" };

int liczbaOpcjiSP = 3;
string opcjeSP[] = { "Algorytm Dijsktry", "Algorytm Bellmana-Forda", "Wyœwietl graf" };

int liczbaOpcjiMST = 3;
string opcjeMST[] = { "Algorytm Prima", "Algorytm Kurskala", "Wyœwietl graf" };

int liczbaOpcjiMF = 2;
string opcjeMF[] = { "Algorytm Forda-Fulkresona", "Algorytm Kurskala", "Wyœwietl graf" };

int liczbaOpcjiReprezentacja = 2;
string opcjeReprezentacja[] = { "Macierz s¹siedztwa", "Lista s¹siedztwa" };



void menuSP(Dane*);
bool czyPrzed(int a, int b) {
	return a > b;
}

using namespace std;

int main() {
	
	setlocale(LC_ALL, "polish");
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| SDiZO - zadanie projektowe nr 2                                          |" << endl;
	cout << "| Autor: Miko³aj Chmielecki                                                |" << endl;
	cout << "| Data realizacji projektu: 2021-05-26                                     |" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;

	Menu menu = Menu(liczbaOpcji, opcje, "Menu g³ówne");
	Dane* dane = new Dane();
	
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
		{
			menuSP(dane);
		}
		break;

		case 1:
		{
		}
		break;
		case 2:
		{
		}
		break;
		case 3:
		{
			dane->menu();
		}
		break;
		}
	}
	delete dane;
}


ReprezentacjaGrafu wyborReprezentacji() {
	Menu menu = Menu(liczbaOpcjiReprezentacja, opcjeReprezentacja, "Wybierz typ reprezentacji grafu");
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			return ReprezentacjaGrafu::MACIERZ;
		case 1:
			return ReprezentacjaGrafu::LISTA;
		}
	}
	return ReprezentacjaGrafu::NONE;
}


void menuSP(Dane* dane) {
	TypAlgorytmu typ = TypAlgorytmu::SP;
	Menu menu = Menu(liczbaOpcjiSP, opcjeSP, "Najkrótsza œcie¿ka");
	ReprezentacjaGrafu reprezentacja = wyborReprezentacji();

	// nie wybrano reprezentacji
	if (reprezentacja == ReprezentacjaGrafu::NONE) {
		return;
	}
	IGraf* graf = nullptr;
	BellmanFord* bellmanFord = nullptr;
	try {
		graf = dane->getGraf(reprezentacja, TypAlgorytmu::SP);
	}
	catch (exception e) {
		cout << e.what() << endl;
		return;
	}
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			break;
		case 1:
			bellmanFord = new BellmanFord(graf);
			try {
				bellmanFord->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Bellmana-Forda:" << endl << bellmanFord->getWynik();
			}
			catch (exception e) {
				cout << e.what() << endl;
				return;
			}
			delete bellmanFord;
			break;
		case 2:
			cout << graf->toString();
			break;
		}
	}


	delete graf;
	
}

