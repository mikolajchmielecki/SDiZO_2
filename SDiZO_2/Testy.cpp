#include "Testy.h"

void Testy::uruchomTesty() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	Kruskal* kruskal = new Kruskal();
	Prim* prim = new Prim();
	BellmanFord* bellmanFord = new BellmanFord(false);
	Dijkstra* dijkstra = new Dijkstra(true);
	FordFulkerson* fordFulkersonBFS = new FordFulkerson(TrybPrzeszukiwania::BFS);
	FordFulkerson* fordFulkersonDFS = new FordFulkerson(TrybPrzeszukiwania::DFS);
	long long int start = read_QPC();
	int liczbaWierzcholkow = 500;

	testujAlgorytm(kruskal, liczbaWierzcholkow, TypAlgorytmu::KRUSKAL);
	testujAlgorytm(prim, liczbaWierzcholkow, TypAlgorytmu::PRIM);
	testujAlgorytm(bellmanFord, liczbaWierzcholkow, TypAlgorytmu::BELLMANFORD);
	testujAlgorytm(dijkstra, liczbaWierzcholkow, TypAlgorytmu::DIJKSTRA);

	liczbaWierzcholkow = 50;
	testujAlgorytm(fordFulkersonDFS, liczbaWierzcholkow, TypAlgorytmu::FORDFURKELSON);
	testujAlgorytm(fordFulkersonBFS, liczbaWierzcholkow, TypAlgorytmu::FORDFURKELSON);
	

	long long int czas = read_QPC() - start;
	cout <<  "[INFO] Czas trwania: "<< czas / frequency << " s";

	delete kruskal;
	delete prim;
	delete bellmanFord;
	delete dijkstra;
	delete fordFulkersonBFS;
	delete fordFulkersonDFS;

}

/*
Testuje pojedynczy algorytm dla dwoch reprezentacji oraz 4 ró¿nych gêstoœci
*/
void Testy::testujAlgorytm(IAlgorytm* algorytm, int maksymalnaLiczbaWierzcholkow, TypAlgorytmu typAlgorytmu) {
	float gestosci[4] = { 0.25, 0.5, 0.75, 0.99 };
	for (int i = 0; i < 4; i++) {
		testujPrzypadek(algorytm, gestosci[i], maksymalnaLiczbaWierzcholkow, ReprezentacjaGrafu::MACIERZ, typAlgorytmu);
		testujPrzypadek(algorytm, gestosci[i], maksymalnaLiczbaWierzcholkow, ReprezentacjaGrafu::LISTA, typAlgorytmu);
	}
}

/*
Testuje dany przypadek dla ró¿nych liczb wierzcho³ków
*/
void Testy::testujPrzypadek(IAlgorytm* algorytm, float gestosc, int maksymalnaLiczbaWierzcholkow, ReprezentacjaGrafu reprezentacja, TypAlgorytmu typAlgorytmu) {
	const int liczbaRozmiarow = 10;
	int rozmiar = maksymalnaLiczbaWierzcholkow / liczbaRozmiarow;
	int skok = rozmiar;
	double srednieCzasy[liczbaRozmiarow];

	string reprezentacjaString = "";
	if (reprezentacja == ReprezentacjaGrafu::MACIERZ) {
		reprezentacjaString = "macierz";
	}
	else {
		reprezentacjaString = "lista";
	}
	string naglowek = algorytm->getNazwa() + "(" + reprezentacjaString + "," + to_string((int)round(gestosc*100)) + "%)";
	for (int i = 0; i < liczbaRozmiarow; i++) {
		LosowyGraf* losowyGraf = new LosowyGraf(typAlgorytmu, reprezentacja, rozmiar, gestosc);
		srednieCzasy[i] = getSredniCzas(algorytm, losowyGraf);
		cout << "[INFO] " << naglowek << " " << to_string(rozmiar) << " " << to_string(srednieCzasy[i]) << endl;
		delete losowyGraf;
		rozmiar += skok;
	}
	string wynik = naglowek + "\n";
	wynik += wynikToString(liczbaRozmiarow, maksymalnaLiczbaWierzcholkow, srednieCzasy);

	naglowek.erase(remove(naglowek.begin(), naglowek.end(), '%'), naglowek.end());
	naglowek.erase(remove(naglowek.begin(), naglowek.end(), ')'), naglowek.end());

	replace(naglowek.begin(), naglowek.end(), '(', '_');
	replace(naglowek.begin(), naglowek.end(), ',', '_');

	zapisz(naglowek, wynik);
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

/*
Stukrotnie testuje dany algorytm z zadanym grafem
*/
double Testy::getSredniCzas(IAlgorytm* algorytm, LosowyGraf* losowyGraf) {
	const int liczbaTestow = 100;
	double sumaCzasow = 0;
	

	for (int i = 0; i < liczbaTestow; i++) {
		IGraf* graf = losowyGraf->losuj();
		algorytm->inicjalizuj(graf);
		long long int start = read_QPC();
		algorytm->uruchom();
		long long int czas = read_QPC() - start;
		algorytm->zwolnij();
		delete graf;
		sumaCzasow += 1000000.0 * czas / frequency;
	}
	return sumaCzasow / liczbaTestow;
}

string Testy::wynikToString(int liczbaRozmiarow, int maksymalnyRozmiar, double* srednieCzasy) {
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
	ofstream zapis(nazwaPliku + ".csv");
	zapis << dane;
	zapis.close();
}

