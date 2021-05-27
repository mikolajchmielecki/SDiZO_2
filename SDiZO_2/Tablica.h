#pragma once


/*
Odpowiednik STL.vector
*/
template<class T>
class Tablica {
public:
	Tablica(int rozmiar);
	~Tablica();
	T* tablica;
	void dodaj(T element, int pozycja);
	void usun(int pozycja);
	int getRozmiar();
	void sortuj(bool (*czyPrzed)(T,T));
private:
	void zwolnijTablice();
	int rozmiar;
	void quickSort(int l, int p);
	int partycjonowanie(int l, int p);
	bool (*czyPrzed)(T, T);

};















