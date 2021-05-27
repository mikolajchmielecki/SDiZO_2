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



/*
Sortuje tablicê danych
Jako argument przyjmuje fukncjê porównuj¹c¹ dwa argumenty
*/
template<class T>
void Tablica<T>::sortuj(bool (*czyPrzed)(T, T)) {
	this->czyPrzed = czyPrzed;
	quickSort(0, rozmiar - 1);
}



/*
Realizuje algorytm sortowania szybkiego
*/
template<class T>
void Tablica<T>::quickSort(int l, int p) {
	if (l >= p) return;
	int m = partycjonowanie(l, p);
	quickSort(l, m);
	quickSort(m + 1, p);
}


/*
Dzieli tablicê na dwie czêœci
Po lewej stronie s¹ wartoœci mniejsze lub równe od pivota
Po prawej stronie s¹ wartoœci wiêksze lub równe od pivota
*/
template<class T>
int Tablica<T>::partycjonowanie(int lewy, int prawy) {
	T pivot = tablica[lewy];
	int l = lewy;
	int p = prawy;
	while (true) {
		while (czyPrzed(tablica[l], pivot)) ++l;
		while (czyPrzed(pivot, tablica[p])) --p;
		if (l < p) {
			swap(tablica[l], tablica[p]);
			++l;
			--p;
		}
		else {
			if (p == prawy) p--;
			return p;
		}
	}
}


template<class T>
void Tablica<T>::zwolnijTablice() {
	delete[] tablica;
}















