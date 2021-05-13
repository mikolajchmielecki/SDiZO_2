#include<iostream>
#include<locale.h>
#include<string>
#include "Menu.h"
#include "Typy.h"
#include "IGraf.h"
#include "GrafMacierz.h"
#include "GrafLista.h"
#include "MySTL.h"


using namespace std;


int liczbaOpcji = 2;
string opcje[] = { "dane","testy" };



int main() {
	
	setlocale(LC_ALL, "polish");
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| SDiZO - zadanie projektowe nr 2                                          |" << endl;
	cout << "| Autor: Miko³aj Chmielecki                                                |" << endl;
	cout << "| Data realizacji projektu: 2021-05-26                                     |" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;

	Menu menu = Menu(liczbaOpcji, opcje, "Menu g³ówne");
	GrafLista* grafLista = new GrafLista(10, 10, 0, 2, false);
	IGraf* graf = grafLista;
	graf->dodajKrawedz(1, 2, 10);
	graf->dodajKrawedz(1, 3, 11);
	cout << graf->toString();
	delete grafLista;

	GrafMacierz* grafMacierz = new GrafMacierz(10, 10, 0, 2, false);
	IGraf* graf1 = grafMacierz;
	graf1->dodajKrawedz(1, 2, 10);
	graf1->dodajKrawedz(1, 3, 11);
	cout << graf1->toString();
	delete grafMacierz;
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
		{
			
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
		}
	}
}

