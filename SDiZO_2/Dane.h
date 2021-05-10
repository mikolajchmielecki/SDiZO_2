#pragma once
#include<string>
#include "TablicaDynamiczna.h"

using namespace std;

class Dane {
public:
	Dane(TablicaDynamiczna*);
	TablicaDynamiczna* getTablica();
	void menu();
	
private:
	void ustawSciezke();
	void wczytaj();
	string * menuString;
	int liczbaOpcji;
	TablicaDynamiczna* tablica;
	string sciezka;
};

