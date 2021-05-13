#pragma once
#include<string>
#include "GrafMacierz.h"
#include "GrafLista.h"
#include "IGraf.h"
#include "Typy.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include "Menu.h"

using namespace std;

/*
Klasa odpowiada za wczytywanie danych z pliku tekstowego.
*/
class Dane {
public:
	Dane();
	IGraf* getGraf(ReprezentacjaGrafu, TypAlgorytmu);
	void menu();
	
private:
	void ustawSciezke();
	int liczbaOpcji;
	string sciezka;
	int* podzielInt(int, string);
};

