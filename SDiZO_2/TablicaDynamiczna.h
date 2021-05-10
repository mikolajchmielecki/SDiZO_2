#pragma once
#include <string>
#include "IStrukturyLiniowe.h"


using namespace std;

class TablicaDynamiczna : public IStrukturyLiniowe {
public:
	TablicaDynamiczna(int rozmiar, int tablica[]);
	TablicaDynamiczna();
	TablicaDynamiczna(const TablicaDynamiczna &tablica);
	~TablicaDynamiczna();
	int* tablica;
	virtual void dodajPoczatek(int liczba);
	virtual void dodajKoniec(int liczba);
	virtual void dodaj(int liczba, int pozycja);
	virtual void usunPoczatek();
	virtual void usunKoniec();
	virtual void usun(int pozycja);
	virtual int wyszukaj(int liczba);
	void wyswietl();
	int getRozmiar();
	int* getTablica();
	int* getTablicaKopia();
	void zamien(int, int);
	void generujLosoweDane(int);
	int getLosowaLiczba();
private:
	int rozmiar;
	int losowaLiczba;
	

};