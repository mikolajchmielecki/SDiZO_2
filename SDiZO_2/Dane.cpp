#include "Dane.h"


using namespace std;



Dane::Dane() {
	liczbaOpcji = 2;
	sciezka = "dane.txt";
}

void Dane::menu() {
	
	string tablica[] = { "ustaw �cie�k�", "wy�wietl �cie�k�" };
	Menu menu = Menu(liczbaOpcji, tablica, "Dane");
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			ustawSciezke();
			cout << "�cie�ka ustawiona" << endl;
			break;

		case 1:
			cout << sciezka << endl;
			break;
		}
	}
}


void Dane::ustawSciezke() {
	cout << "Wprowad� �cie�k�: ";
	cin >> sciezka;
}

/*
Przekszta�ca string na tablice int�w.
Liczba int�w zadana w parametrrze.
Nale�y zwolni� pami�� po skorzystaniu
*/
int* Dane::podzielInt(int liczba, string tekst) {
	int* tablica = new int[liczba];
	stringstream ss;
	ss << tekst;
	string temp;
	int i = 0;
	while (!ss.eof()) {
		ss >> temp;
		int tmpLiczba;
		if (stringstream(temp) >> tmpLiczba && i < liczba) {
			tablica[i] = tmpLiczba;
			i++;
		}
		temp = "";
		
	}
	if (i < liczba) {
		throw exception("[ERROR] B��d formatu danych");
	}
	return tablica;
}

/*
Wczytywanie danych z pliku
Zwraca dane w tablicy dynamicznej

a. w pierwszej linii zapisana jest informacja o grafie (jednolita dla wszystkich
problem�w): liczba kraw�dzi, liczba wierzcho�k�w, wierzcho�ek pocz�tkowy,
wierzcho�ek ko�cowy (rozdzielone bia�ymi znakami). W przypadku MST warto��
dw�ch ostatnich parametr�w jest nieistotna, dla najkr�tszej �cie�ki zignorowana
powinna by� warto�� wierzcho�ka ko�cowego,

b. wierzcho�ki numerowane s� w spos�b ci�g�y od zera,

c. w kolejnych liniach znajduj� si� opisy kraw�dzi (ka�da kraw�d� w osobnej linii) w
postaci trzech liczb rozdzielonych bia�ymi znakami (wierzcho�ek pocz�tkowy,
wierzcho�ek ko�cowy oraz waga/przepustowo��),

d. dla problemu MST kraw�dzie traktowane s� jako nieskierowane, natomiast dla
algorytm�w najkr�tszej �cie�ki i maksymalnego przep�ywu jako skierowane,

*/
IGraf* Dane::getGraf(ReprezentacjaGrafu reprezentacja, TypAlgorytmu typAlgorytmu, bool czyDuplikaty) {
	ifstream plik;
	plik.open(sciezka);
	IGraf* graf = nullptr;

	int liczbaKrawedzi = 0;
	int liczbaWierzcholkow = 0;
	int wierzcholekStartowy = -1;
	int wierzcholekKoncowy = -1;
	
	if (plik.is_open())
	{
		string naglowek = "";
		getline(plik, naglowek);
		if (plik.fail())
			throw exception("[ERROR] B��d wczytania nag��wka grafu z pliku");

		int naglowekLiczba = 0;
		if (typAlgorytmu == TypAlgorytmu::SP) {
			naglowekLiczba = 3;
		} else if (typAlgorytmu == TypAlgorytmu::MST) {
			naglowekLiczba = 2;
		} else if (typAlgorytmu == TypAlgorytmu::MF) {
			naglowekLiczba = 4;
		}

		int* tablica = nullptr;
		try {
			tablica = podzielInt(naglowekLiczba, naglowek);
		}
		catch (exception e) {
			throw exception("[ERROR] B��d wczytania nag��wka grafu z pliku");
		}
		//wczytywanie rozmiaru
		liczbaKrawedzi = tablica[0];
		if (liczbaKrawedzi <= 0) {
			throw exception("[ERROR] B��d wczytania liczby kraw�dzi");
		}

		liczbaWierzcholkow = tablica[1];
		if (liczbaWierzcholkow <= 0) {
			throw exception("[ERROR] B��d wczytania liczby wierzcho�k�w");
		}
		if (typAlgorytmu == TypAlgorytmu::SP || typAlgorytmu == TypAlgorytmu::MF) {
			wierzcholekStartowy = tablica[2];
			if (wierzcholekStartowy < 0 || wierzcholekStartowy >= liczbaWierzcholkow) {
				throw exception("[ERROR] B��d wczytania wierzcho�ka startowego");
			}
		}
		if (typAlgorytmu == TypAlgorytmu::MF) {
			wierzcholekKoncowy = tablica[3];
			if (wierzcholekKoncowy < 0 || wierzcholekKoncowy >= liczbaWierzcholkow) {
				throw exception("[ERROR] B��d wczytania wierzcho�ka ko�cowego");
			}
		}
		delete tablica;
		if (plik.fail())
			throw exception("[ERROR] B��d wczytania rozmiaru grafu z pliku");
		else {
			if (reprezentacja == ReprezentacjaGrafu::LISTA) {
				graf = new GrafLista(liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekKoncowy, czyDuplikaty, typAlgorytmu);
			}
			else if (reprezentacja == ReprezentacjaGrafu::MACIERZ) {
				graf = new GrafMacierz(liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekKoncowy, czyDuplikaty, typAlgorytmu);
			}

		}

		for (int i = 0; i < liczbaKrawedzi; i++) {
			string linia = "";
			getline(plik, linia);
			if (plik.fail())
				throw exception("[ERROR] B��d wczytania kraw�dzi");

			int* krawedzTablica = podzielInt(3, linia);

			// nie akceptujemy kraw�dzi mi�dzy tym samym wierzcho�kiem
			if (krawedzTablica[0] == krawedzTablica[1]) {
				throw exception("[ERROR] Pocz�tek i koniec kraw�dzi to ten sam wierzcho�ek");
			}

			/*
			// dla graf�w nieskierowanych pocz�tek musi by� wi�kszy od ko�ca
			if (typAlgorytmu == TypAlgorytmu::MST && krawedzTablica[0] < krawedzTablica[1]) {
				swap(krawedzTablica[0], krawedzTablica[1]);
			}
			*/

			graf->dodajKrawedz(krawedzTablica[0], krawedzTablica[1], krawedzTablica[2]);
			delete krawedzTablica;
		}

		plik.close();
	}
	else
		throw exception("[ERROR] B��d otwartcia pliku");

	return graf;
	
}





