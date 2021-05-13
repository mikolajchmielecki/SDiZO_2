#include "Tablica.h"

/*
Tworzy tablicê dynamiczn¹
*/
template<class T>
Tablica<T>::Tablica(int rozmiar) {
	this->rozmiar = rozmiar;
	this->tablica = new T[rozmiar];
}


/*
Zwalnia pamiêæ wszystkich elementów tablicy
*/
template<class T>
Tablica<T>::~Tablica() {
	zwolnijTablice();
}


/*
Dodaje na konkretn¹ pozycjê, powiêksza zaalokowany obszar o 1
*/
template<class T>
void Tablica<T>::dodaj(T element, int pozycja) {
	if (pozycja > rozmiar || pozycja < 0) {
		throw "Poza zakresem";
	}
	rozmiar++;

	//tworzenie nowej wiêkszej tablicy
	T* temp = new T[rozmiar];

	//kopiowanie starej tablicy do nowej
	// i - indeksuje now¹ tablica
	// indeks - indeksuje star¹ tablicê
	for (int i = 0, indeks = 0; i < rozmiar; i++) {

		if (i == pozycja) {
			//wstawianie nowego elementu
			temp[i] = element;
		}
		else {
			temp[i] = tablica[indeks];
			indeks++;
		}
	}
	zwolnijTablice();
	tablica = temp;
}

/*
Usuwa element na zadanej pozycji
*/
template<class T>
void Tablica<T>::usun(int pozycja) {
	//sprawdzanie zakresu
	if (pozycja >= rozmiar || pozycja < 0) {
		throw "Poza zakresem";
	}

	rozmiar--;
	T* temp = nullptr;
	if (rozmiar > 0) {
		//tworzenie nowej wiêkszej tablicy
		temp = new T[rozmiar];
	}

	//kopiowanie starej tablicy do nowej
	// i - indeksuje now¹ tablica
	// indeks - indeksuje star¹ tablicê
	for (int i = 0, indeks = 0; i < rozmiar; indeks++) {

		if (indeks == pozycja) {
			continue;
		}
		else {
			temp[i] = tablica[indeks];
			i++;
		}
	}
	zwolnijTablice();
	tablica = temp;
}

template<class T>
int Tablica<T>::getRozmiar() {
	return rozmiar;
}

template<class T>
void Tablica<T>::zwolnijTablice() {
	delete[] tablica;
}













