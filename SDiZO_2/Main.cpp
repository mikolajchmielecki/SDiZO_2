#include<iostream>
#include<locale.h>
#include<string>
#include "TablicaDynamiczna.h"
#include "Dane.h"
#include "Menu.h"
#include "Lista.h"
#include "Kopiec.h"
#include "Testy.h"


using namespace std;


int liczbaOpcji = 2;
string opcje[] = { "dane","testy" };

TablicaDynamiczna* graf = new TablicaDynamiczna();


int main() {
	setlocale(LC_ALL, "polish");
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| SDiZO - zadanie projektowe nr 2                                          |" << endl;
	cout << "| Autor: Miko³aj Chmielecki                                                |" << endl;
	cout << "| Data realizacji projektu: 2021-05-26                                     |" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;

	Menu menu = Menu(liczbaOpcji, opcje, "Menu g³ówne");
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
			
		case 0:
		{
			Dane dane = Dane(graf);
			dane.menu();
			graf = dane.getTablica();
			
		}
		break;
		case 1:
		{
			Testy* testy = new Testy();
			testy->wykonajTesty();
			delete testy;
		}
		break;
		}
	}
	delete graf;
}

