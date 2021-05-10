#include "Testy.h"
#include<iostream>
//bilbioteka wykorzystywana do zamiany spacji na podkreœlniki w nazwie pliku
#include<algorithm>
#include <random>


using namespace std;


Testy::Testy() {
	frequency = 0;
	start = 0;
	koniec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	//liczba realizowanych testów dla danego rozmiaru struktury
	liczbaPomiarow = 100;
	//liczba ró¿nych rozmiarów
	liczbaRozmiarow = 10;
	

	
}

void Testy::wykonajTesty() {
	
	cout << "Testy tablica..." << endl;
	
	int rozmiarTablica = 2000000;
	wykonajTest(Operacja::TablicaDodajKoniec, rozmiarTablica);
	wykonajTest(Operacja::TablicaDodajPoczatek, rozmiarTablica);
	wykonajTest(Operacja::TablicaDodajSrodek, rozmiarTablica);
	wykonajTest(Operacja::TablicaUsunPoczatek, rozmiarTablica);
	wykonajTest(Operacja::TablicaUsunSrodek, rozmiarTablica);
	wykonajTest(Operacja::TablicaUsunKoniec, rozmiarTablica);
	wykonajTest(Operacja::TablicaWyszukaj, rozmiarTablica);
	
	cout << "Testy lista..." << endl;
	
	int listaRozmiar = 100000;
	wykonajTest(Operacja::ListaDodajKoniec, listaRozmiar);
	wykonajTest(Operacja::ListaDodajPoczatek, listaRozmiar);
	wykonajTest(Operacja::ListaDodajSrodek, listaRozmiar);
	wykonajTest(Operacja::ListaUsunPoczatek, listaRozmiar);
	wykonajTest(Operacja::ListaUsunSrodek, listaRozmiar);
	wykonajTest(Operacja::ListaUsunKoniec, listaRozmiar);
	wykonajTest(Operacja::ListaWyszukaj, listaRozmiar);
	
	cout << "Testy kopiec..." << endl;
	int kopiecRozmiar = 2000000;
	wykonajTest(Operacja::KopiecDodaj, kopiecRozmiar);
	wykonajTest(Operacja::KopiecUsun, kopiecRozmiar);
	wykonajTest(Operacja::KopiecWyszukaj, kopiecRozmiar);
	
	cout << "Testy RB..." << endl;
	int RBRozmiar = 200000;
	wykonajTest(Operacja::RBDodaj, RBRozmiar);
	wykonajTest(Operacja::RBUsun, RBRozmiar);
	wykonajTest(Operacja::RBWyszukaj, RBRozmiar);
	cout << "Testy AVL..." << endl;
	int AVLRozmiar = 200000;
	wykonajTest(Operacja::AVLDodaj, AVLRozmiar);
	wykonajTest(Operacja::AVLUsun, AVLRozmiar);
	wykonajTest(Operacja::AVLWyszukaj, AVLRozmiar);

	cout << "Testy STL List..." << endl;

	int rozmiarSTLList = 1000000;
	wykonajTest(Operacja::STLListDodajKoniec, rozmiarSTLList);
	wykonajTest(Operacja::STLListDodajPoczatek, rozmiarSTLList);
	wykonajTest(Operacja::STLListDodajSrodek, rozmiarSTLList);
	wykonajTest(Operacja::STLListUsunPoczatek, rozmiarSTLList);
	wykonajTest(Operacja::STLListUsunSrodek, rozmiarSTLList);
	wykonajTest(Operacja::STLListUsunKoniec, rozmiarSTLList);
	wykonajTest(Operacja::STLListWyszukaj, rozmiarSTLList);

	cout << "Testy STL Vector..." << endl;

	int rozmiarSTLVector = 2000000;
	wykonajTest(Operacja::STLVectorDodajKoniec, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorDodajPoczatek, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorDodajSrodek, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorUsunPoczatek, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorUsunSrodek, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorUsunKoniec, rozmiarSTLVector);
	wykonajTest(Operacja::STLVectorWyszukaj, rozmiarSTLVector);


}

void Testy::wykonajTest(Operacja operacja, int maksymalnyRozmiar) {
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> zakresInt(-2147483648, 2147483647); // zakres wartoœci int
	double* srednieCzasy = new double[liczbaRozmiarow];
	double* czasyRozmiar = new double[liczbaPomiarow];

	int minimalnyRozmiar = maksymalnyRozmiar / liczbaRozmiarow;
	
	//pêtla iteruj¹ca po zadanych rozmiarach
	for (int i = 0; i < liczbaRozmiarow; i++) {
		//cout << rozmiary[i] << endl;
		//pêtla powtarzaj¹ca dzia³anie dla tego samego rozmiaru
		for (int j = 0; j < liczbaPomiarow; j++) {
			TablicaDynamiczna* tablica = new TablicaDynamiczna();
			tablica->generujLosoweDane(minimalnyRozmiar*(i+1));
			int losowaLiczba = tablica->getLosowaLiczba();	// liczba losowa zawarta w tablicy
			int nowaLosowaLiczba = zakresInt(gen);
			int pozycja = -1;
			Lista* lista = NULL;
			Kopiec* kopiec = NULL;
			Drzewo* rb = NULL;
			Drzewo* avl = NULL;
			STLList* list = NULL;
			STLVector* vector = NULL;

			switch (operacja) {

			//-----------TABLICA------------------
			case Operacja::TablicaDodajPoczatek:
				start = read_QPC();
				tablica->dodajPoczatek(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaDodajKoniec:
				start = read_QPC();
				tablica->dodajKoniec(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaDodajSrodek:
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				tablica->dodaj(nowaLosowaLiczba, pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaUsunPoczatek:
				start = read_QPC();
				tablica->usunPoczatek();
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaUsunKoniec:
				start = read_QPC();
				tablica->usunKoniec();
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaUsunSrodek:
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				tablica->usun(pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::TablicaWyszukaj:
				start = read_QPC();
				tablica->wyszukaj(losowaLiczba);
				koniec = read_QPC() - start;
				break;


			//---------LISTA----------------
			case Operacja::ListaDodajPoczatek:
				lista = new Lista(tablica);
				start = read_QPC();
				lista->dodajPoczatek(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaDodajKoniec:
				lista = new Lista(tablica);
				start = read_QPC();
				lista->dodajKoniec(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaDodajSrodek:
				lista = new Lista(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				lista->dodaj(nowaLosowaLiczba, pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaUsunPoczatek:
				lista = new Lista(tablica);
				start = read_QPC();
				lista->usunPoczatek();
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaUsunKoniec:
				lista = new Lista(tablica);
				start = read_QPC();
				lista->usunKoniec();
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaUsunSrodek:
				lista = new Lista(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				lista->usun(pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::ListaWyszukaj:
				lista = new Lista(tablica);
				start = read_QPC();
				lista->wyszukaj(losowaLiczba);
				koniec = read_QPC() - start;
				break;


			//----------KOPIEC----------
			case Operacja::KopiecDodaj:
				kopiec = new Kopiec(tablica);
				start = read_QPC();
				kopiec->dodaj(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::KopiecUsun:
				kopiec = new Kopiec(tablica);
				start = read_QPC();
				kopiec->usun();
				koniec = read_QPC() - start;
				break;
			case Operacja::KopiecWyszukaj:
				kopiec = new Kopiec(tablica);
				start = read_QPC();
				kopiec->wyszukaj(losowaLiczba, false);
				koniec = read_QPC() - start;
				break;


			//---------RB------------------
			case Operacja::RBDodaj:
				rb = new Drzewo(tablica,Typ::RB);
				start = read_QPC();
				rb->dodaj(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::RBUsun:
				rb = new Drzewo(tablica, Typ::RB);
				start = read_QPC();
				rb->usun(losowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::RBWyszukaj:
				rb = new Drzewo(tablica, Typ::RB);
				start = read_QPC();
				rb->wyszukaj(losowaLiczba, false);
				koniec = read_QPC() - start;
				break;


			//---------AVL------------------
			case Operacja::AVLDodaj:
				avl = new Drzewo(tablica, Typ::AVL);
				start = read_QPC();
				avl->dodaj(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::AVLUsun:
				avl = new Drzewo(tablica, Typ::AVL);
				start = read_QPC();
				avl->usun(losowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::AVLWyszukaj:
				avl = new Drzewo(tablica, Typ::AVL);
				start = read_QPC();
				avl->wyszukaj(losowaLiczba, false);
				koniec = read_QPC() - start;
				break;

				//---------STLList----------------
			case Operacja::STLListDodajPoczatek:
				list = new STLList(tablica);
				start = read_QPC();
				list->dodajPoczatek(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListDodajKoniec:
				list = new STLList(tablica);
				start = read_QPC();
				list->dodajKoniec(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListDodajSrodek:
				list = new STLList(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				list->dodaj(nowaLosowaLiczba, pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListUsunPoczatek:
				list = new STLList(tablica);
				start = read_QPC();
				list->usunPoczatek();
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListUsunKoniec:
				list = new STLList(tablica);
				start = read_QPC();
				list->usunKoniec();
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListUsunSrodek:
				list = new STLList(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				list->usun(pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLListWyszukaj:
				list = new STLList(tablica);
				start = read_QPC();
				list->wyszukaj(losowaLiczba);
				koniec = read_QPC() - start;
				break;


			//---------STLVector----------------
			case Operacja::STLVectorDodajPoczatek:
				vector = new STLVector(tablica);
				start = read_QPC();
				vector->dodajPoczatek(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorDodajKoniec:
				vector = new STLVector(tablica);
				start = read_QPC();
				vector->dodajKoniec(nowaLosowaLiczba);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorDodajSrodek:
				vector = new STLVector(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				vector->dodaj(nowaLosowaLiczba, pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorUsunPoczatek:
				vector = new STLVector(tablica);
				start = read_QPC();
				vector->usunPoczatek();
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorUsunKoniec:
				vector = new STLVector(tablica);
				start = read_QPC();
				vector->usunKoniec();
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorUsunSrodek:
				vector = new STLVector(tablica);
				pozycja = tablica->getRozmiar() / 2;
				start = read_QPC();
				vector->usun(pozycja);
				koniec = read_QPC() - start;
				break;
			case Operacja::STLVectorWyszukaj:
				vector = new STLVector(tablica);
				start = read_QPC();
				vector->wyszukaj(losowaLiczba);
				koniec = read_QPC() - start;
				break;

			
			}
			czasyRozmiar[j] = 1000000.0 * koniec / frequency;
			if (lista != NULL) {
				delete lista;
			}
			if (kopiec != NULL) {
				delete kopiec;
			}
			if (rb != NULL) {
				delete rb;
			}
			if(avl != NULL) {
				delete avl;
			}
			if (list != NULL) {
				delete list;
			}
			if (vector != NULL) {
				delete vector;
			}
			delete tablica;
		}
		srednieCzasy[i] = sredniCzas(czasyRozmiar);
	}
	string wynik = nazwa(operacja) + "\n";
	wynik += wynikToString(maksymalnyRozmiar, srednieCzasy);
	zapisz(nazwaPliku(operacja), wynik);
	delete[] srednieCzasy;
	delete[] czasyRozmiar;

}

double Testy::sredniCzas(double* tablica) {
	double suma = 0;
	for (int i = 0; i < liczbaPomiarow; i++) {
		suma += tablica[i];
	}
	return suma / liczbaPomiarow;
}

string Testy::wynikToString(int maksymalnyRozmiar, double* srednieCzasy) {
	string wynik = "";
	int minimalnyRozmiar = maksymalnyRozmiar / liczbaRozmiarow;
	for (int i = 0; i < liczbaRozmiarow; i++) {
		wynik += to_string(minimalnyRozmiar * (i + 1));
		wynik += ";";
		wynik += to_string(srednieCzasy[i]);
		wynik += ";\n";
	}
	return wynik;
}

void Testy::zapisz(string nazwaPliku, string dane) {
	ofstream zapis(nazwaPliku+".csv");
	zapis << dane;
	zapis.close();
}


/*
Pomiar aktualnego czasu
*/
long long int Testy::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

string Testy::nazwa(Operacja operacja) {
	string wynik = "";
	switch (operacja) {
	case Operacja::TablicaDodajKoniec:
		wynik = "Tablica: dodawanie na koniec";
		break;
	case Operacja::TablicaDodajPoczatek:
		wynik = "Tablica: dodawanie na poczatek";
		break;
	case Operacja::TablicaDodajSrodek:
		wynik = "Tablica: dodawanie na srodek";
		break;
	case Operacja::TablicaUsunKoniec:
		wynik = "Tablica: usuwanie z konca";
		break;
	case Operacja::TablicaUsunPoczatek:
		wynik = "Tablica: usuwanie z poczatku";
		break;
	case Operacja::TablicaUsunSrodek:
		wynik = "Tablica: usuwanie ze srodka";
		break;
	case Operacja::TablicaWyszukaj:
		wynik = "Tablica: wyszukiwanie";
		break;
	case Operacja::ListaDodajKoniec:
		wynik = "Lista: dodawanie na koniec";
		break;
	case Operacja::ListaDodajPoczatek:
		wynik = "Lista: dodawanie na poczatek";
		break;
	case Operacja::ListaDodajSrodek:
		wynik = "Lista: dodawanie na srodek";
		break;
	case Operacja::ListaUsunKoniec:
		wynik = "Lista: usuwanie z konca";
		break;
	case Operacja::ListaUsunPoczatek:
		wynik = "Lista: usuwanie z poczatku";
		break;
	case Operacja::ListaUsunSrodek:
		wynik = "Lista: usuwanie ze srodka";
		break;
	case Operacja::ListaWyszukaj:
		wynik = "Lista: wyszukaj";
		break;
	case Operacja::KopiecDodaj:
		wynik = "Kopiec: dodawanie";
		break;
	case Operacja::KopiecUsun:
		wynik = "Kopiec: usuwanie";
		break;
	case Operacja::KopiecWyszukaj:
		wynik = "Kopiec: wyszukiwanie";
		break;
	case Operacja::RBDodaj:
		wynik = "RB: dodawanie";
		break;
	case Operacja::RBUsun:
		wynik = "RB: usuwanie";
		break;
	case Operacja::RBWyszukaj:
		wynik = "RB: wyszukiwanie";
		break;
	case Operacja::AVLDodaj:
		wynik = "AVL: dodawanie";
		break;
	case Operacja::AVLUsun:
		wynik = "AVL: usuwanie";
		break;
	case Operacja::AVLWyszukaj:
		wynik = "AVL: wyszukiwanie";
		break;
	case Operacja::STLListDodajKoniec:
		wynik = "STL List: dodawanie na koniec";
		break;
	case Operacja::STLListDodajPoczatek:
		wynik = "STL List: dodawanie na poczatek";
		break;
	case Operacja::STLListDodajSrodek:
		wynik = "STL List: dodawanie na srodek";
		break;
	case Operacja::STLListUsunKoniec:
		wynik = "STL List: usuwanie z konca";
		break;
	case Operacja::STLListUsunPoczatek:
		wynik = "STL List: usuwanie z poczatku";
		break;
	case Operacja::STLListUsunSrodek:
		wynik = "STL List: usuwanie ze srodka";
		break;
	case Operacja::STLListWyszukaj:
		wynik = "STL List: wyszukiwanie";
		break;
	case Operacja::STLVectorDodajKoniec:
		wynik = "STL Vector: dodawanie na koniec";
		break;
	case Operacja::STLVectorDodajPoczatek:
		wynik = "STL Vector: dodawanie na poczatek";
		break;
	case Operacja::STLVectorDodajSrodek:
		wynik = "STL Vector: dodawanie na srodek";
		break;
	case Operacja::STLVectorUsunKoniec:
		wynik = "STL Vector: usuwanie z konca";
		break;
	case Operacja::STLVectorUsunPoczatek:
		wynik = "STL Vector: usuwanie z poczatku";
		break;
	case Operacja::STLVectorUsunSrodek:
		wynik = "STL Vector: usuwanie ze srodka";
		break;
	case Operacja::STLVectorWyszukaj:
		wynik = "STL Vector: wyszukiwanie";
		break;
	}
	return wynik;
}

string Testy::nazwaPliku(Operacja operacja) {
	string nazwaString = nazwa(operacja);
	
	replace(nazwaString.begin(), nazwaString.end(), ':', '_');
	//zamiana spacji na podkreœlniki
	replace(nazwaString.begin(), nazwaString.end(), ' ', '_');
	
	return nazwaString;
}
