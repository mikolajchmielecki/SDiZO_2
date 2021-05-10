#pragma once
#include<string>
#include<fstream>
#include "TablicaDynamiczna.h"
#include "Dane.h"
#include "Menu.h"
#include "MenuStrukturyLiniowe.h"
#include "MenuStrukturyDrzewiaste.h"
#include "Lista.h"
#include "Kopiec.h"
#include "Drzewo.h"
#include <windows.h>
#include <iomanip>
#include "Typy.h"
#include "STLList.h"
#include "STLVector.h"

class Testy {
public:
	Testy();
	void wykonajTesty();
private:
	int liczbaPomiarow;
	int liczbaRozmiarow;
	string sciezka;
	void wykonajTest(Operacja, int);
	double sredniCzas(double* tablica);
	string wynikToString(int , double* );
	void zapisz(string, string);
	long long int start, koniec, frequency;
	long long int read_QPC();
	string nazwa(Operacja);
	string nazwaPliku(Operacja);
};

