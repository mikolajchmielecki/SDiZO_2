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
#include "FordFulkerson.h"
#include "LosowyGraf.h"
#include "Testy.h"


// SP - shortest path
// MST - minimal spaning tree
// MF - max flow

// Teksty wyœwietlane w menu

int liczbaOpcji = 5;
string opcje[] = { "Najkrótsza œcie¿ka", "Minimalne drzewo rozpinaj¹ce", "Maksymalny przep³yw", "Dane", "Testy" };

int liczbaOpcjiSP = 3;
string opcjeSP[] = { "Algorytm Dijsktry", "Algorytm Bellmana-Forda", "Wyœwietl graf" };

int liczbaOpcjiMST = 3;
string opcjeMST[] = { "Algorytm Prima", "Algorytm Kurskala", "Wyœwietl graf" };

int liczbaOpcjiMF = 3;
string opcjeMF[] = { "Algorytm Forda-Fulkresona BFS", "Algorytm Forda-Fulkresona DFS", "Wyœwietl graf" };

int liczbaOpcjiReprezentacja = 2;
string opcjeReprezentacja[] = { "Macierz s¹siedztwa", "Lista s¹siedztwa" };



void menuSP(Dane*);
void menuMST(Dane*);
void menuMF(Dane*);


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
			menuMF(dane);
			break;
		case 3:
		{
			dane->menu();
		}
		break;
		case 4:
		{
			Testy* testy = new Testy();
			testy->uruchomTesty();
			delete testy;
			
		}
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

IGraf* wczytajGraf(Dane* dane, ReprezentacjaGrafu reprezentacja, TypProblemu typAlgorytmu, bool czyDuplikaty) {
	return dane->getGraf(reprezentacja, typAlgorytmu, czyDuplikaty);


}


void menuSP(Dane* dane) {
	TypProblemu typ = TypProblemu::SP;
	Menu menu = Menu(liczbaOpcjiSP, opcjeSP, "Najkrótsza œcie¿ka");
	
	
	
	while (menu.czyUruchomione()) {
		IGraf* graf = nullptr;
		switch (menu.wyswietl()) {
		case 0:
		{
			Dijkstra* dijkstra = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				dijkstra = new Dijkstra(false);
				dijkstra->inicjalizuj(graf);
				dijkstra->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Dijkstry:" << endl << dijkstra->getWynik();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (dijkstra != nullptr) {
				delete dijkstra;
			}
			break;
		}
		case 1:
		{
			BellmanFord* bellmanFord = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				bellmanFord = new BellmanFord();
				bellmanFord->inicjalizuj(graf);
				bellmanFord->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Bellmana-Forda:" << endl << bellmanFord->getWynik();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (bellmanFord != nullptr) {
				delete bellmanFord;
			}
			break;
		}
		case 2:
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				cout << graf->toString();
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
	TypProblemu typ = TypProblemu::MST;
	Menu menu = Menu(liczbaOpcjiMST, opcjeMST, "Minimalne drzewo rozpinaj¹ce");
	
	

	while (menu.czyUruchomione()) {
		IGraf* graf = nullptr;
		switch (menu.wyswietl()) {
		case 0:
		{
			Prim* prim = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				prim = new Prim();
				prim->inicjalizuj(graf);
				prim->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Prima:" << endl << prim->getWynik();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (prim != nullptr) {
				delete prim;
			}
			break;
		}
		case 1:
		{
			Kruskal* kruskal = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, false);
				kruskal = new Kruskal();
				kruskal->inicjalizuj(graf);
				kruskal->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Kruskala:" << endl << kruskal->getWynik();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (kruskal != nullptr) {
				delete kruskal;
			}
			break;
		}
		case 2:
			try {
				ReprezentacjaGrafu reprezentacja = wyborReprezentacji();
				graf = wczytajGraf(dane, reprezentacja, typ, true);
				cout << "Dla algorytmu Prima:" << endl;
				cout << graf->toString();
				delete graf;
				cout << endl;
				cout << "Dla algorytmu Kruskala:" << endl;
				graf = wczytajGraf(dane, reprezentacja, typ, false);
				cout << graf->toString();
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

void menuMF(Dane* dane) {
	TypProblemu typ = TypProblemu::MF;
	Menu menu = Menu(liczbaOpcjiMF, opcjeMF, "Maksymalny przep³yw");
	

	while (menu.czyUruchomione()) {
		IGraf* graf = nullptr;
		switch (menu.wyswietl()) {
		case 0:
		{
			FordFulkerson* fordFulkerson = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				fordFulkerson = new FordFulkerson(TrybPrzeszukiwania::BFS);
				fordFulkerson->inicjalizuj(graf);
				fordFulkerson->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Forda-Fulekrsona BFS:" << endl << fordFulkerson->getWynik();

			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (fordFulkerson != nullptr) {
				delete fordFulkerson;
			}
			break;
		}
		case 1:
		{
			FordFulkerson* fordFulkerson = nullptr;
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				fordFulkerson = new FordFulkerson(TrybPrzeszukiwania::DFS);
				fordFulkerson->inicjalizuj(graf);
				fordFulkerson->uruchom();
				cout << endl << endl << "Wynika dzia³ania algorytmu Forda-Fulekrsona DFS:" << endl << fordFulkerson->getWynik();

			}
			catch (exception e) {
				cout << e.what() << endl;
			}
			if (fordFulkerson != nullptr) {
				delete fordFulkerson;
			}
			break;
		}
		case 2:
			try {
				graf = wczytajGraf(dane, wyborReprezentacji(), typ, true);
				graf->inicjalizujPrzeplywy();
				cout << graf->toString();
				
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

