#include "Dane.h"


using namespace std;



Dane::Dane() {
	liczbaOpcji = 2;
	sciezka = "dane.txt";
}

void Dane::menu() {
	
	string tablica[] = { "ustaw œcie¿kê", "wyœwietl œcie¿kê" };
	Menu menu = Menu(liczbaOpcji, tablica, "Dane");
	while (menu.czyUruchomione()) {
		switch (menu.wyswietl()) {
		case 0:
			ustawSciezke();
			cout << "Œcie¿ka ustawiona" << endl;
			break;

		case 1:
			cout << sciezka << endl;
			break;
		}
	}
}


void Dane::ustawSciezke() {
	cout << "WprowadŸ œcie¿kê: ";
	cin >> sciezka;
}

/*
Przekszta³ca string na tablice intów.
Liczba intów zadana w parametrrze.
Nale¿y zwolniæ pamiêæ po skorzystaniu
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
		throw exception("[ERROR] B³¹d formatu danych");
	}
	return tablica;
}

/*
Wczytywanie danych z pliku
Zwraca dane w tablicy dynamicznej

a. w pierwszej linii zapisana jest informacja o grafie (jednolita dla wszystkich
problemów): liczba krawêdzi, liczba wierzcho³ków, wierzcho³ek pocz¹tkowy,
wierzcho³ek koñcowy (rozdzielone bia³ymi znakami). W przypadku MST wartoœæ
dwóch ostatnich parametrów jest nieistotna, dla najkrótszej œcie¿ki zignorowana
powinna byæ wartoœæ wierzcho³ka koñcowego,

b. wierzcho³ki numerowane s¹ w sposób ci¹g³y od zera,

c. w kolejnych liniach znajduj¹ siê opisy krawêdzi (ka¿da krawêdŸ w osobnej linii) w
postaci trzech liczb rozdzielonych bia³ymi znakami (wierzcho³ek pocz¹tkowy,
wierzcho³ek koñcowy oraz waga/przepustowoœæ),

d. dla problemu MST krawêdzie traktowane s¹ jako nieskierowane, natomiast dla
algorytmów najkrótszej œcie¿ki i maksymalnego przep³ywu jako skierowane,

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
			throw exception("[ERROR] B³¹d wczytania nag³ówka grafu z pliku");

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
			throw exception("[ERROR] B³¹d wczytania nag³ówka grafu z pliku");
		}
		//wczytywanie rozmiaru
		liczbaKrawedzi = tablica[0];
		if (liczbaKrawedzi <= 0) {
			throw exception("[ERROR] B³¹d wczytania liczby krawêdzi");
		}

		liczbaWierzcholkow = tablica[1];
		if (liczbaWierzcholkow <= 0) {
			throw exception("[ERROR] B³¹d wczytania liczby wierzcho³ków");
		}
		if (typAlgorytmu == TypAlgorytmu::SP || typAlgorytmu == TypAlgorytmu::MF) {
			wierzcholekStartowy = tablica[2];
			if (wierzcholekStartowy < 0 || wierzcholekStartowy >= liczbaWierzcholkow) {
				throw exception("[ERROR] B³¹d wczytania wierzcho³ka startowego");
			}
		}
		if (typAlgorytmu == TypAlgorytmu::MF) {
			wierzcholekKoncowy = tablica[3];
			if (wierzcholekKoncowy < 0 || wierzcholekKoncowy >= liczbaWierzcholkow) {
				throw exception("[ERROR] B³¹d wczytania wierzcho³ka koñcowego");
			}
		}
		delete tablica;
		if (plik.fail())
			throw exception("[ERROR] B³¹d wczytania rozmiaru grafu z pliku");
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
				throw exception("[ERROR] B³¹d wczytania krawêdzi");

			int* krawedzTablica = podzielInt(3, linia);

			// nie akceptujemy krawêdzi miêdzy tym samym wierzcho³kiem
			if (krawedzTablica[0] == krawedzTablica[1]) {
				throw exception("[ERROR] Pocz¹tek i koniec krawêdzi to ten sam wierzcho³ek");
			}

			/*
			// dla grafów nieskierowanych pocz¹tek musi byæ wiêkszy od koñca
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
		throw exception("[ERROR] B³¹d otwartcia pliku");

	return graf;
	
}





