#include "Lista.h"

using namespace std;


template<class T>
Lista<T>::Lista() {
	rozmiar = 0;
	glowa = nullptr;
	ogon = nullptr;
}

/*
Zwalnia pamiêæ zajmowan¹ przez listê
*/
template<class T>
Lista<T>::~Lista() {
	ElementListy<T>* iterator = glowa;
	for (int i = 0; i < rozmiar; i++) {
		ElementListy<T>* temp = iterator->nastepny;
		delete iterator;
		iterator = temp;
	}
}


/*
Tworzy listê z wczytanych danych
*/
/*
template<class T>
Lista<T>::Lista(Tablica<T>* tablica) {
	this->rozmiar = tablica->getRozmiar();
	glowa = nullptr;
	ogon = nullptr;
	//inicjalizuje pust¹ tablicê
	if (rozmiar < 1) {
		rozmiar = 0;
		glowa = nullptr;
		ogon = nullptr;;
		return;
	}
	//tworzy listê na podstwie kolejnych elementów tablicy
	else {
		ElementListy<T>* element = nullptr;

		//pamiêta poprzedni element
		ElementListy<T>* bufor = nullptr;
		for (int i = 0; i < rozmiar; i++) {
			element = new ElementListy<T>;
			element->element = tablica->getTablica()[i];

			//pierwszy element listy
			if (i == 0) {
				glowa = element;
				glowa->poprzedni = nullptr;
			}

			//ostatni element listy
			if (i == rozmiar - 1) {
				if (rozmiar == 1) {
					ogon = element;
					ogon->nastepny = nullptr;
					ogon->poprzedni = nullptr;
				}
				else {
					ogon = element;
					ogon->nastepny = nullptr;
					ogon->poprzedni = bufor;
					bufor->nastepny = ogon;
				}

			}

			//pozosta³e elementy listy
			if (i > 0 && i < rozmiar - 1) {
				bufor->nastepny = element;
				element->poprzedni = bufor;
			}

			bufor = element;
		}
	}
}
*/

/*
Dodaje element na pocz¹tek listy
Zmienia wskaŸnik g³owy
*/
template<class T>
void Lista<T>::dodajPoczatek(T element) {
	ElementListy<T>* nowy = new ElementListy<T>;
	nowy->element = element;
	nowy->poprzedni = nullptr;
	nowy->nastepny = glowa;
	if (glowa == nullptr) {
		ogon = nowy;
	}
	else {
		glowa->poprzedni = nowy;
	}
	glowa = nowy;
	rozmiar++;
}

/*
Dodaje element na koniec listy
Korzysta z tego, ¿e pamiêty jest wskaŸnik na ogon
*/
template<class T>
void Lista<T>::dodajKoniec(T element) {
	ElementListy<T>* nowy = new ElementListy<T>;
	nowy->element = element;
	nowy->poprzedni = ogon;
	nowy->nastepny = nullptr;
	if (ogon == nullptr) {
		glowa = nowy;
	}
	else {
		ogon->nastepny = nowy;
	}
	ogon = nowy;
	rozmiar++;
}

/*
Dodaje na konkretn¹ pozycjê, powiêksza zaalokowany obszar o 1
*/
template<class T>
void Lista<T>::dodaj(T element, int pozycja) {
	if (pozycja > rozmiar || pozycja < 0) {
		throw exception("[ERROR] Poza zakresem");
	}


	if (pozycja == 0) {
		dodajPoczatek(element);
		return;
	}
	else if (pozycja == rozmiar) {
		dodajKoniec(element);
		return;
	}
	//przechodzenie od pocz¹tku listy

	else if (pozycja < rozmiar / 2) {
		ElementListy<T>* nowy = new ElementListy<T>;
		nowy->element = element;
		ElementListy<T>* iterator = glowa;
		for (int i = 0; i < pozycja - 1; i++) {
			iterator = iterator->nastepny;
		}
		//iterator wskazuje element poprzedaj¹cy nowy element
		nowy->nastepny = iterator->nastepny;
		nowy->poprzedni = iterator;
		iterator->nastepny->poprzedni = nowy;
		iterator->nastepny = nowy;


	}
	//przechodzenie od koñca listy
	else {
		ElementListy<T>* nowy = new ElementListy<T>;
		nowy->element = element;
		ElementListy<T>* iterator = ogon;
		for (int i = rozmiar - 1; i > pozycja; i--) {
			iterator = iterator->poprzedni;
		}
		//iterator wskazuje element nastêpny dla nowego elementu
		nowy->poprzedni = iterator->poprzedni;
		nowy->nastepny = iterator;
		iterator->poprzedni->nastepny = nowy;
		iterator->poprzedni = nowy;
	}
	rozmiar++;
}

template<class T>
void Lista<T>::usunPoczatek() {
	//czy mo¿na cokolwiek usun¹æ
	if (rozmiar > 0) {
		rozmiar--;
		//czy istnieje nastêpny element po g³owie
		if (glowa->nastepny != nullptr) {
			glowa->nastepny->poprzedni = nullptr;
			ElementListy<T>* temp = glowa->nastepny;
			delete glowa;
			glowa = temp;
		}
		else {
			delete glowa;
			glowa = nullptr;
			ogon = nullptr;
		}

	}
	else {
		throw exception("[ERROR] Brak elementów do usuniêcia");
	}
}

template<class T>
void Lista<T>::usunKoniec() {
	//czy mo¿na cokolwiek usun¹æ
	if (rozmiar > 0) {
		rozmiar--;
		//czy istnieje poprzedni element ogona
		if (ogon->poprzedni != nullptr) {
			ogon->poprzedni->nastepny = nullptr;
			ElementListy<T>* temp = ogon->poprzedni;
			delete ogon;
			ogon = temp;
		}
		else {
			delete ogon;
			glowa = nullptr;
			ogon = nullptr;
		}

	}
	else {
		throw exception("[ERROR] Brak elementów do usuniêcia");
	}
}

template<class T>
void Lista<T>::usun(int pozycja) {
	//sprawdzanie zakresu
	if (pozycja >= rozmiar || pozycja < 0) {
		throw exception("[ERROR] Poza zakresem");
	}

	//element na pocz¹tku
	if (pozycja == 0) {
		usunPoczatek();
		return;
	}
	//element na koñcu
	else if (pozycja == rozmiar - 1) {
		usunKoniec();
		return;
	}
	//przechodzenie od pocz¹tku listy
	else if (pozycja < rozmiar / 2) {
		ElementListy<T>* iterator = glowa;
		for (int i = 0; i < pozycja - 1; i++) {
			iterator = iterator->nastepny;
		}
		//iterator wskazuje element poprzedaj¹cy usuwany element element
		ElementListy<T>* elementUsuwany = iterator->nastepny;
		iterator->nastepny = elementUsuwany->nastepny;
		elementUsuwany->nastepny->poprzedni = iterator;
		delete elementUsuwany;
	}
	//przechodzenie od koñca listy
	else {
		ElementListy<T>* iterator = ogon;
		for (int i = rozmiar - 1; i > pozycja; i--) {
			iterator = iterator->poprzedni;
		}
		//iterator wskazuje na usuwany element
		iterator->nastepny->poprzedni = iterator->poprzedni;
		iterator->poprzedni->nastepny = iterator->nastepny;
		delete iterator;
	}
	rozmiar--;

}

template<class T>
T Lista<T>::getElement(int pozycja) {
	if (rozmiar == 0 || pozycja < 0 || pozycja >= rozmiar) {
		throw exception("[ERROR] Poza zakresem");
	}

	// przechodzenie od pocz¹tku listy
	if (pozycja < rozmiar / 2) {
		ElementListy<T>* iterator = glowa;
		for (int i = 0; i < pozycja; i++) {
			iterator = iterator->nastepny;
		}
		return iterator->element;
	}
	//przechodzenie od koñca listy
	else {
		ElementListy<T>* iterator = ogon;
		for (int i = rozmiar - 1; i > pozycja; i--) {
			iterator = iterator->poprzedni;
		}
		return iterator->element;
	}
}


/*
Zwraca wskaŸnik na g³owe
Przyspiesza iterowanie po liscie
*/
template<class T>
ElementListy<T>* Lista<T>::getIterator() {
	return glowa;

}


/*
Sprawdzenie czy lista zawiera zadany element
W parametrze jest wyszukiwany element oraz funkcja porównuj¹ca
*/
template<class T>
template<typename F>
bool Lista<T>::czyZawiera(T element, F porownajF) {
	ElementListy<T>* iterator = glowa;
	for (int i = 0; i < rozmiar; i++) {
		if (porownajF(iterator->element, element)) {
			return true;
		}
		iterator = iterator->nastepny;
	}
	return false;

}

template<class T>
int Lista<T>::getRozmiar() {
	return rozmiar;
}






