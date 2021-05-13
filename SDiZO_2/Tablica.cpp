#include "Tablica.h"

/*
Tworzy tablic� dynamiczn�
*/
template<class T>
Tablica<T>::Tablica(int rozmiar) {
	this->rozmiar = rozmiar;
	this->tablica = new T[rozmiar];
}


/*
Zwalnia pami�� wszystkich element�w tablicy
*/
template<class T>
Tablica<T>::~Tablica() {
	zwolnijTablice();
}


/*
Dodaje na konkretn� pozycj�, powi�ksza zaalokowany obszar o 1
*/
template<class T>
void Tablica<T>::dodaj(T element, int pozycja) {
	if (pozycja > rozmiar || pozycja < 0) {
		throw "Poza zakresem";
	}
	rozmiar++;

	//tworzenie nowej wi�kszej tablicy
	T* temp = new T[rozmiar];

	//kopiowanie starej tablicy do nowej
	// i - indeksuje now� tablica
	// indeks - indeksuje star� tablic�
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
		//tworzenie nowej wi�kszej tablicy
		temp = new T[rozmiar];
	}

	//kopiowanie starej tablicy do nowej
	// i - indeksuje now� tablica
	// indeks - indeksuje star� tablic�
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













