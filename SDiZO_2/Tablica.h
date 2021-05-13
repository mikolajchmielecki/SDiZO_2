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
private:
	void zwolnijTablice();
	int rozmiar;

};















