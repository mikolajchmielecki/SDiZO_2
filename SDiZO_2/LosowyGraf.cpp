#include "LosowyGraf.h"

LosowyGraf::LosowyGraf(TypAlgorytmu typAlgorytmu, ReprezentacjaGrafu reprezentacja, int liczbaWierzcholkow, float gestosc) {
	this->typAlgorytmu = typAlgorytmu;
	this->reprezentacja = reprezentacja;
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	this->wierzcholekStartowy = 0;
	this->wierzcholekKoncowy = liczbaWierzcholkow - 1;

	if (typAlgorytmu == TypAlgorytmu::BELLMANFORD || typAlgorytmu == TypAlgorytmu::DIJKSTRA || typAlgorytmu == TypAlgorytmu::FORDFURKELSON) {
		this->czyDuplikaty = true;
		this->czySkierowany = true;
		this->liczbaKrawedzi = (int)(gestosc * liczbaWierzcholkow * (liczbaWierzcholkow - 1));
	}
	if (typAlgorytmu == TypAlgorytmu::KRUSKAL) {
		this->czyDuplikaty = false;
		this->czySkierowany = false;
		this->liczbaKrawedzi = (int)(gestosc * liczbaWierzcholkow * (liczbaWierzcholkow - 1) / 2);
	}
	if (typAlgorytmu == TypAlgorytmu::PRIM) {
		this->czyDuplikaty = true;
		this->czySkierowany = false;
		this->liczbaKrawedzi = (int)(gestosc * liczbaWierzcholkow * (liczbaWierzcholkow - 1) / 2);
	}
	
	
}

IGraf* LosowyGraf::losuj() {
	GrafMacierz* grafMacierz = nullptr;
	if (typAlgorytmu == TypAlgorytmu::BELLMANFORD || typAlgorytmu == TypAlgorytmu::DIJKSTRA) {
		grafMacierz = losujSP();
	}
	if (typAlgorytmu == TypAlgorytmu::FORDFURKELSON) {
		grafMacierz = losujMF();
	}
	if (typAlgorytmu == TypAlgorytmu::KRUSKAL || typAlgorytmu == TypAlgorytmu::PRIM) {
		grafMacierz = losujMST();
	}
	
	if (reprezentacja == ReprezentacjaGrafu::MACIERZ) {
		return grafMacierz;
	}
	else {
		GrafLista* grafLista = nullptr;
		// unikniecie kopiowania macierzy przeplywow
		if (grafMacierz->typAlgorytmu == TypProblemu::MF) {
			grafMacierz->typAlgorytmu = TypProblemu::SP;
			grafLista = grafMacierz->getGrafLista();
			grafLista->typAlgorytmu = TypProblemu::MF;
		}
		else {
			grafLista = grafMacierz->getGrafLista();
		}
		
		delete grafMacierz;

		return grafLista;
	}

}

GrafMacierz* LosowyGraf::losujSP() {
	GrafMacierz* grafMacierz = new GrafMacierz(liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekKoncowy, czyDuplikaty, TypProblemu::SP);
	Tablica<Tablica<int>*>* macierz = grafMacierz->getMacierz();

	int aktualnaLiczbaKrawedzi = 0;
	
	// tworzenie œcie¿ki od wierzcho³ka startowego do ka¿dego innego wierzcho³ka
	for (int i = 1; i < liczbaWierzcholkow; i++) {
		int dlugoscSciezki = getLosowaLiczba(1, liczbaWierzcholkow/10+1);
		int poprzednik = wierzcholekStartowy;
		bool czyKoniec = false;
		for (; dlugoscSciezki > 0; dlugoscSciezki--) {
			int nastepnik = getLosowaLiczba(1, liczbaWierzcholkow - 1);

			// je¿eli chcielibysmy utworzyæ pêtle
			if (poprzednik == nastepnik) {
				continue;
			}

			if (macierz->tablica[poprzednik]->tablica[nastepnik] == INT_MAX) {
				macierz->tablica[poprzednik]->tablica[nastepnik] = getLosowaWaga();
				aktualnaLiczbaKrawedzi++;
			}

			// je¿eli osi¹gneliœmy koniec 
			if (nastepnik == i) {
				czyKoniec = true;
				break;
			}
			poprzednik = nastepnik;
		}
		if (czyKoniec == false) {
			if (macierz->tablica[poprzednik]->tablica[i] == INT_MAX) {
				macierz->tablica[poprzednik]->tablica[i] = getLosowaWaga();
				aktualnaLiczbaKrawedzi++;
			}
		}
	}

	// dope³nianie do zadanej gêstoœci
	while (aktualnaLiczbaKrawedzi < liczbaKrawedzi) {
		int start = getLosowaLiczba(0, liczbaWierzcholkow-1);
		int koniec = getLosowaLiczba(0, liczbaWierzcholkow - 1);

		// szukanie najblizeszego wolnego miejsca
		while ( (start != koniec && macierz->tablica[start]->tablica[koniec] == INT_MAX) == false) {
			koniec++;
			if (koniec == liczbaWierzcholkow) {
				koniec = 0;
				start++;
				if (start == liczbaWierzcholkow) {
					start = 0;
				}
			}
		}
		macierz->tablica[start]->tablica[koniec] = getLosowaWaga();
		aktualnaLiczbaKrawedzi++;
		
	}

	grafMacierz->liczbaKrawedzi = aktualnaLiczbaKrawedzi;
	return grafMacierz;
}

GrafMacierz* LosowyGraf::losujMF() {
	GrafMacierz* grafMacierz = new GrafMacierz(liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekKoncowy, czyDuplikaty, TypProblemu::MF);
	Tablica<Tablica<int>*>* macierz = grafMacierz->getMacierz();

	int aktualnaLiczbaKrawedzi = 0;
	int liczbaSciezek = getLosowaLiczba(1, liczbaWierzcholkow/10+1);
	// tworzenie œcie¿ki od wierzcho³ka startowego do ka¿dego innego wierzcho³ka
	for (int i = 1; i < liczbaWierzcholkow; i++) {
		int dlugoscSciezki = getLosowaLiczba(1, liczbaWierzcholkow/10+1);
		int poprzednik = wierzcholekStartowy;
		bool czyKoniec = false;
		for (; dlugoscSciezki > 0; dlugoscSciezki--) {
			int nastepnik = getLosowaLiczba(1, liczbaWierzcholkow - 1);

			// je¿eli chcielibysmy utworzyæ pêtle
			if (poprzednik == nastepnik) {
				continue;
			}

			if (macierz->tablica[poprzednik]->tablica[nastepnik] == INT_MAX) {
				macierz->tablica[poprzednik]->tablica[nastepnik] = getLosowaWaga();
				aktualnaLiczbaKrawedzi++;
			}

			// je¿eli osi¹gneliœmy koniec 
			if (nastepnik == wierzcholekKoncowy) {
				czyKoniec = true;
				break;
			}
			poprzednik = nastepnik;
		}
		if (czyKoniec == false) {
			if (macierz->tablica[poprzednik]->tablica[wierzcholekKoncowy] == INT_MAX) {
				macierz->tablica[poprzednik]->tablica[wierzcholekKoncowy] = getLosowaWaga();
				aktualnaLiczbaKrawedzi++;
			}
		}
	}

	// dope³nianie do zadanej gêstoœci
	while (aktualnaLiczbaKrawedzi < liczbaKrawedzi) {
		int start = getLosowaLiczba(0, liczbaWierzcholkow - 1);
		int koniec = getLosowaLiczba(0, liczbaWierzcholkow - 1);

		// szukanie najblizeszego wolnego miejsca
		while ((start != koniec && macierz->tablica[start]->tablica[koniec] == INT_MAX) == false) {
			koniec++;
			if (koniec == liczbaWierzcholkow) {
				koniec = 0;
				start++;
				if (start == liczbaWierzcholkow) {
					start = 0;
				}
			}
		}
		macierz->tablica[start]->tablica[koniec] = getLosowaWaga();
		aktualnaLiczbaKrawedzi++;

	}

	grafMacierz->liczbaKrawedzi = aktualnaLiczbaKrawedzi;
	return grafMacierz;
}

GrafMacierz* LosowyGraf::losujMST() {
	GrafMacierz* grafMacierz = new GrafMacierz(liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekKoncowy, czyDuplikaty, TypProblemu::MST);
	Tablica<Tablica<int>*>* macierz = grafMacierz->getMacierz();

	int aktualnaLiczbaKrawedzi = 0;
	int wierzcholekCentralny = getLosowaLiczba(0, liczbaWierzcholkow - 1);

	// tworzenie puktu centarlnego
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (i == wierzcholekCentralny) {
			continue;
		}
		int waga = getLosowaWaga();
		grafMacierz->dodajKrawedz(wierzcholekCentralny, i, waga);
		aktualnaLiczbaKrawedzi++;
	}


	// dope³nianie do zadanej gêstoœci
	while (aktualnaLiczbaKrawedzi < liczbaKrawedzi) {
		// losowanie z lewgo dolnego trójk¹ta
		int start = getLosowaLiczba(1, liczbaWierzcholkow - 1);
		int koniec = getLosowaLiczba(0, start - 1);
		
		
		// szukanie najblizeszego wolnego miejsca
		while ((start != koniec && macierz->tablica[start]->tablica[koniec] == INT_MAX) == false) {
			koniec++;
			if (koniec == start) {
				koniec = 0;
				start++;
				if (start == liczbaWierzcholkow) {
					start = 1;
				}
			}
		}
		int waga = getLosowaWaga();
		grafMacierz->dodajKrawedz(start, koniec, waga);
		aktualnaLiczbaKrawedzi++;

	}

	grafMacierz->liczbaKrawedzi = aktualnaLiczbaKrawedzi;
	return grafMacierz;
}

/*
Zwraca dopuszczalne wagi dla kazdego algorytmu
*/
int LosowyGraf::getLosowaWaga() {
	int waga_min = -1000000;
	int waga_max = 1000000;
	if (typAlgorytmu == TypAlgorytmu::BELLMANFORD || typAlgorytmu == TypAlgorytmu::PRIM || typAlgorytmu == TypAlgorytmu::KRUSKAL) {
		return getLosowaLiczba(waga_min, waga_max);
	}
	if (typAlgorytmu == TypAlgorytmu::DIJKSTRA) {
		return getLosowaLiczba(0, waga_max);
	}
	if (typAlgorytmu == TypAlgorytmu::FORDFURKELSON) {
		return getLosowaLiczba(1, waga_max);
	}
	return 0;
}

/*
Losuje liczbe ca³kowit¹ z zadanego przedzia³u z krañcami w³¹cznie
*/
int LosowyGraf::getLosowaLiczba(int min, int max) {
	static random_device rd; // non-deterministic generator
	static mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> zakresDanych(min, max);
	return zakresDanych(gen);
}
