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
#include "Dijkstra.h"
#include "Kruskal.h"
#include "Prim.h"


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
void menuMST(Dane*);
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
			menuSP(dane);
			break;

		case 1:
			menuMST(dane);
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
	throw exception("");
}

IGraf* wczytajGraf(Dane* dane, ReprezentacjaGrafu reprezentacja, TypAlgorytmu typAlgorytmu, bool czyDuplikaty) {
	return dane->getGraf(reprezentacja, typAlgorytmu, czyDuplikaty);


}


void menuSP(Dane* dane) {
	TypAlgorytmu typ = TypAlgorytmu::SP;
	Menu menu = Menu(liczbaOpcjiSP, opcjeSP, "Najkrótsza œcie¿ka");
	IGraf* graf = nullptr;
	BellmanFord* bellmanFord = nullptr;
	Dijkstra* dijkstra = nullptr;
	
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			
			try {
				dijkstra = new Dijkstra(wczytajGraf(dane, wyborReprezentacji(), typ, true), false);
				dijkstra->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Dijkstry:" << endl << dijkstra->getWynik();
				delete dijkstra;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			
			break;
		case 1:
			
			try {
				bellmanFord = new BellmanFord(wczytajGraf(dane, wyborReprezentacji(), typ, true));
				bellmanFord->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Bellmana-Forda:" << endl << bellmanFord->getWynik();
				delete bellmanFord;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			
			break;
		case 2:
			try {
				cout << wczytajGraf(dane, wyborReprezentacji(), typ, true)->toString();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}

		if (graf != nullptr) {
			delete graf;
		}
	}
	
}


void menuMST(Dane* dane) {
	TypAlgorytmu typ = TypAlgorytmu::MST;
	Menu menu = Menu(liczbaOpcjiMST, opcjeMST, "Minimalne drzewo rozpinaj¹ce");
	IGraf* graf = nullptr;
	Prim* prim = nullptr;
	Kruskal* kruskal = nullptr;

	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:

			try {
				prim = new Prim(wczytajGraf(dane, wyborReprezentacji(), typ, true));
				prim->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Prima:" << endl << prim->getWynik();
				delete prim;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}

			break;
		case 1:

			try {
				kruskal = new Kruskal(wczytajGraf(dane, wyborReprezentacji(), typ, false));
				kruskal->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Kruskala:" << endl << kruskal->getWynik();
				delete kruskal;
			}
			catch (exception e) {
				cout << e.what() << endl;
			}

			break;
		case 2:
			try {
				ReprezentacjaGrafu reprezentacja = wyborReprezentacji();
				cout << "Dla algorytmu Prima:" << endl;
				cout << wczytajGraf(dane, reprezentacja, typ, true)->toString();
				cout << endl;
				cout << "Dla algorytmu Kruskala:" << endl;
				cout << wczytajGraf(dane, reprezentacja, typ, false)->toString();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			break;
		}

		if (graf != nullptr) {
			delete graf;
		}
	}
}

