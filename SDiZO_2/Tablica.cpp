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



/*
Sortuje tablic� danych
Jako argument przyjmuje fukncj� por�wnuj�c� dwa argumenty
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
Dzieli tablic� na dwie cz�ci
Po lewej stronie s� warto�ci mniejsze lub r�wne od pivota
Po prawej stronie s� warto�ci wi�ksze lub r�wne od pivota
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















