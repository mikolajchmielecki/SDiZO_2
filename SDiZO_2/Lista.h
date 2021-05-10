#pragma once
#include "IStrukturyLiniowe.h"
#include "TablicaDynamiczna.h"

struct Element {
	Element* poprzedni;
	Element* nastepny;
	int liczba;
};

class Lista : public IStrukturyLiniowe{
public:
	Lista();
	~Lista();
	Lista(TablicaDynamiczna* tablica);
	virtual void dodajPoczatek(int);
	virtual void dodajKoniec(int liczba);
	virtual void dodaj(int liczba, int pozycja);
	virtual void usunPoczatek();
	virtual void usunKoniec();
	virtual void usun(int pozycja);
	virtual int wyszukaj(int liczba);
	virtual void wyswietl();

private:
	int rozmiar;
	Element* glowa;
	Element* ogon;
};

