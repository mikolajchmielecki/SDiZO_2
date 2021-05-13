#pragma once
#include <iostream>

using namespace std;


template<class T>
struct ElementListy {
	ElementListy* poprzedni;
	ElementListy* nastepny;
	T element;
};

template<class T>
class Lista {
public:

	Lista();
	~Lista();
	void dodajPoczatek(T element);
	void dodajKoniec(T element);
	void dodaj(T element, int pozycja);
	void usunPoczatek();
	void usunKoniec();
	void usun(int pozycja);
	T getElement(int pozycja);
	ElementListy<T>* getIterator();

	template<typename F>
	bool czyZawiera(T element, F porownajF);
	int getRozmiar();
	ElementListy<T>* ogon;
	ElementListy<T>* glowa;
private:
	int rozmiar;
	
	
};



