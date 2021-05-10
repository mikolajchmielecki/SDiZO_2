#include "Lista.h"
#include <iostream>
#include "Menu.h"

using namespace std;


/*
Inicjuje pust� list�
*/
Lista::Lista() {
	rozmiar = 0;
	glowa = NULL;
	ogon = NULL;
}

/*
Zwalnia pami�� zajmowan� przez list�
*/
Lista::~Lista() {
	Element* iterator = glowa;
	for (int i = 0; i < rozmiar; i++) {
		Element* temp = iterator->nastepny;
		delete iterator;
		iterator = temp;
	}
}

/*
Tworzy list� z wczytanych danych
*/
Lista::Lista(TablicaDynamiczna* tablica) {
	this->rozmiar = tablica->getRozmiar();
	glowa = NULL;
	ogon = NULL;
	//inicjalizuje pust� tablic�
	if (rozmiar < 1) {
		rozmiar = 0;
		glowa = NULL;
		ogon = NULL;;
		return;
	}
	//tworzy list� na podstwie kolejnych element�w tablicy
	else {
		Element* element = NULL;

		//pami�ta poprzedni element
		Element* bufor = NULL;
		for (int i = 0; i < rozmiar; i++) {
			element = new Element;
			element->liczba = tablica->getTablica()[i];
			
			//pierwszy element listy
			if (i == 0) {
				glowa = element;
				glowa->poprzedni = NULL;
			}

			//ostatni element listy
			if (i == rozmiar - 1) {
				if (rozmiar == 1) {
					ogon = element;
					ogon->nastepny = NULL;
					ogon->poprzedni = NULL;
				}
				else {
					ogon = element;
					ogon->nastepny = NULL;
					ogon->poprzedni = bufor;
					bufor->nastepny = ogon;
				}
				
			}

			//pozosta�e elementy listy
			if(i > 0 && i < rozmiar-1) {
				bufor->nastepny = element;
				element->poprzedni = bufor;
			}

			bufor = element;
		}
	}

}

/*
Dodaje element na pocz�tek listy
Zmienia wska�nik g�owy
*/
void Lista::dodajPoczatek(int liczba) {
	Element* nowy = new Element;
	nowy->liczba = liczba;
	nowy->poprzedni = NULL;
	nowy->nastepny = glowa;
	if (glowa == NULL) {
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
Korzysta z tego, �e pami�ty jest wska�nik na ogon
*/
void Lista::dodajKoniec(int liczba) {
	Element* nowy = new Element;
	nowy->liczba = liczba;
	nowy->poprzedni = ogon;
	nowy->nastepny = NULL;
	if (ogon == NULL) {
		glowa = nowy;
	}
	else {
		ogon->nastepny = nowy;
	}
	ogon = nowy;
	rozmiar++;
}

/*
Dodaje na konkretn� pozycj�, powi�ksza zaalokowany obszar o 1
*/
void Lista::dodaj(int liczba, int pozycja) {
	if (pozycja > rozmiar || pozycja < 0) {
		throw exception("Poza zakresem");
	}

	
	if (pozycja == 0) {
		dodajPoczatek(liczba);
		return;
	} else if (pozycja == rozmiar) {
		dodajKoniec(liczba);
		return;
	}
	//przechodzenie od pocz�tku listy
	
	else if (pozycja < rozmiar / 2) {
		Element* nowy = new Element;
		nowy->liczba = liczba;
		Element* iterator = glowa;
		for (int i = 0; i < pozycja - 1; i++) {
			iterator = iterator->nastepny;
		}
		//iterator wskazuje element poprzedaj�cy nowy element
		nowy->nastepny = iterator->nastepny;
		nowy->poprzedni = iterator;
		iterator->nastepny->poprzedni = nowy;
		iterator->nastepny = nowy;


	}
	//przechodzenie od ko�ca listy
	else {
		Element* nowy = new Element;
		nowy->liczba = liczba;
		Element* iterator = ogon;
		for (int i = rozmiar - 1; i > pozycja; i--) {
			iterator = iterator->poprzedni;
		}
		//iterator wskazuje element nast�pny dla nowego elementu
		nowy->poprzedni = iterator->poprzedni;
		nowy->nastepny = iterator;
		iterator->poprzedni->nastepny = nowy;
		iterator->poprzedni = nowy;
	}
	rozmiar++;
}

void Lista::usunPoczatek() {
	//czy mo�na cokolwiek usun��
	if (rozmiar > 0) {
		rozmiar--;
		//czy istnieje nast�pny element po g�owie
		if (glowa->nastepny != NULL) {
			glowa->nastepny->poprzedni = NULL;
			Element* temp = glowa->nastepny;
			delete glowa;
			glowa = temp;
		}
		else {
			delete glowa;
			glowa = NULL;
			ogon = NULL;
		}
		
	}
	else {
		throw exception("Brak element�w do usuni�cia");
	}
}

void Lista::usunKoniec() {
	//czy mo�na cokolwiek usun��
	if (rozmiar > 0) {
		rozmiar--;
		//czy istnieje poprzedni element ogona
		if (ogon->poprzedni != NULL) {
			ogon->poprzedni->nastepny = NULL;
			Element* temp = ogon->poprzedni;
			delete ogon;
			ogon = temp;
		}
		else {
			delete ogon;
			glowa = NULL;
			ogon = NULL;
		}

	}
	else {
		throw exception("Brak element�w do usuni�cia");
	}
}

/*
Usuwa element na zadanej pozycji
*/
void Lista::usun(int pozycja) {
	//sprawdzanie zakresu
	if (pozycja >= rozmiar || pozycja < 0) {
		throw exception("Poza zakresem");
	}

	//element na pocz�tku
	if (pozycja == 0) {
		usunPoczatek();
		return;
	}
	//element na ko�cu
	 else if (pozycja == rozmiar - 1) {
		usunKoniec();
		return;
	}
	//przechodzenie od pocz�tku listy
	else if (pozycja < rozmiar / 2) {
		Element* iterator = glowa;
		for (int i = 0; i < pozycja - 1; i++) {
			iterator = iterator->nastepny;
		}
		//iterator wskazuje element poprzedaj�cy usuwany element element
		Element* elementUsuwany = iterator->nastepny;
		iterator->nastepny = elementUsuwany->nastepny;
		elementUsuwany->nastepny->poprzedni = iterator;
		delete elementUsuwany;
	}
	//przechodzenie od ko�ca listy
	else {
		Element* iterator = ogon;
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

/*
Wyszukiwanie elementu o zadanej warto�ci
*/
int Lista::wyszukaj(int liczba) {
	Element* iterator = glowa;
	for (int i = 0; i < rozmiar; i++) {
		if (iterator->liczba == liczba) {
			return i;
		}
		iterator = iterator->nastepny;
	}
	throw exception("Brak szukanego elementu");
}

/*
Wy�wietla zawarto�� tablicy
*/
void Lista::wyswietl() {

	cout << "g�owa -> [ ";
	Element* iterator = glowa;
	for (int i = 0; i < rozmiar - 1; i++) {
		cout << iterator->liczba << " , ";
		iterator = iterator->nastepny;
	}
	if (rozmiar > 0) {
		cout << iterator->liczba;
	}
	cout << " ]\n";

	cout << "ogon -> [ ";
	iterator = ogon;
	for (int i = 0; i < rozmiar - 1; i++) {
		cout << iterator->liczba << " , ";
		iterator = iterator->poprzedni;
	}
	if (rozmiar > 0) {
		cout << iterator->liczba;
	}
	cout << " ]\n";
}






