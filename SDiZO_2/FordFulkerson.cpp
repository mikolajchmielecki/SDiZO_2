#include "FordFulkerson.h"

FordFulkerson::FordFulkerson(TrybPrzeszukiwania tryb) {
	this->tryb = tryb;
}

FordFulkerson::~FordFulkerson() {
	if (!zwolniony) {
		// zwalnianie pamiêci zajmowanej prze struktury
		for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
			delete wierzcholki->tablica[i];
		}
		delete wierzcholki;
	}
}

void FordFulkerson::uruchom() {
	// zapamietuje poprzedniki sciezki oraz przepustowosci rezydualne
	wierzcholki = new Tablica<Struktura*>(graf->liczbaWierzcholkow);
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i] = new Struktura(0);
		wierzcholki->tablica[i]->wierzcholek = i;
	}

	graf->inicjalizujPrzeplywy();

	inicjalizujTablicePrzeplywow();

	bool nowaSciezka = znajdzSciezkeRozszerzajaca();
	while (nowaSciezka) {
		int nowyPrzeplyw = wierzcholki->tablica[graf->wierzcholekKoncowy]->klucz;
		maksymalnyPrzeplyw += nowyPrzeplyw;
		int wierzcholek = graf->wierzcholekKoncowy;

		// zmiana przeplywów na sciezce rozszerzajacej
		while (wierzcholek != graf->wierzcholekStartowy) {
			int poprzednik = wierzcholki->tablica[wierzcholek]->poprzednik;

			// zgodnie ze sciezka zwiekszamy przeplyw
			graf->zmienPrzeplyw(poprzednik, wierzcholek, nowyPrzeplyw);

			// przeciwnie do sciezki zmniejszamy przeplyw
			graf->zmienPrzeplyw(wierzcholek, poprzednik, -nowyPrzeplyw);

			wierzcholek = poprzednik;
		}


		inicjalizujTablicePrzeplywow();
		nowaSciezka = znajdzSciezkeRozszerzajaca();
	}
}

/*
S³uzy do sortowania krawedzi w celu wyswietlenia wyniku koncowego
*/
bool czyPrzedFordFulkerson(Krawedz* krawedz1, Krawedz* krawedz2) {
	if (krawedz1->start < krawedz2->start) {
		return true;
	}
	if (krawedz1->start > krawedz2->start) {
		return false;
	}
	if (krawedz1->koniec < krawedz2->koniec) {
		return true;
	}
	return false;
}

/*
Zwraca wynik dzia³ania algorytm Forda-Fulkerosona w postaci tekstowej
Pobiera wszystkie krawedzie i je sortuje.
Nie wyswietla krawedzi o zerowych przeplywach
*/
string FordFulkerson::getWynik() {
	graf->inicjalizujIteratorKrawedzi();
	
	Tablica<Krawedz*>* tablicaKrawedzi = new Tablica<Krawedz*>(graf->liczbaKrawedzi);
	for (int i = 0; i < graf->liczbaKrawedzi; i++) {
		Krawedz* krawedz = graf->nastepnaKrawedz();
		tablicaKrawedzi->tablica[i] = krawedz;
	}

	tablicaKrawedzi->sortuj(&czyPrzedFordFulkerson);
	string wynik = "Start = " + to_string(graf->wierzcholekStartowy) + "   Koniec = " + to_string(graf->wierzcholekKoncowy) + "\n";
	wynik += " Edge\t\tFlow (max/used)\n";

	for (int i = 0; i < graf->liczbaKrawedzi; i++) {
		if (tablicaKrawedzi->tablica[i]->przeplyw > 0) {
			wynik += " ";
			wynik += tablicaKrawedzi->tablica[i]->toString();
			wynik += "/";
			wynik += to_string(tablicaKrawedzi->tablica[i]->przeplyw);
			wynik += "\n";
		}
	}
	wynik += "MAX_FLOW = ";
	wynik += to_string(maksymalnyPrzeplyw);
	wynik += "\n";
	for (int i = 0; i < graf->liczbaKrawedzi; i++) {
		delete tablicaKrawedzi->tablica[i];
	}
	delete tablicaKrawedzi;

	return wynik;
}

void FordFulkerson::inicjalizuj(IGraf* graf) {
	this->graf = graf;
	this->maksymalnyPrzeplyw = 0;
	zwolniony = false;
}

void FordFulkerson::zwolnij() {
	zwolniony = true;
	// zwalnianie pamiêci zajmowanej prze struktury
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		delete wierzcholki->tablica[i];
	}
	delete wierzcholki;
}

string FordFulkerson::getNazwa() {
	string wynik = "Ford-Fulkerson-";
	if (tryb == TrybPrzeszukiwania::BFS) {
		wynik += "BFS";
	}
	else {
		wynik += "DFS";
	}
	return wynik;
}

void FordFulkerson::inicjalizujTablicePrzeplywow() {
	for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
		wierzcholki->tablica[i]->poprzednik = -1;
	}

	// nie odwiedzamy wierzcholka startowego
	wierzcholki->tablica[graf->wierzcholekStartowy]->poprzednik = -2;
	wierzcholki->tablica[graf->wierzcholekStartowy]->klucz = INT_MAX;
}


/*
Dodaje do kolejki wszyskich s¹siadów danego wierzcho³ka w postaci krawedzi
*/
void FordFulkerson::wstawSasiadow(int wierzcholek, Kolejka* kolejka) {
	graf->inicjalizujIteratorSasiadow(wierzcholek);
	// dla ka¿dego s¹siada
	Krawedz* krawedz = graf->nastepnySasiad();
	while (krawedz != nullptr) {
		kolejka->push(krawedz);
		krawedz = graf->nastepnySasiad();
	}
}


bool FordFulkerson::znajdzSciezkeRozszerzajaca() {
	Kolejka* kolejka = new Kolejka(tryb);
	
	wstawSasiadow(graf->wierzcholekStartowy, kolejka);

	// dopóki kolejka nie jest pusta
	while (kolejka->czyPusta() == false) {
		Krawedz* krawedz = kolejka->pop();
		int poprzednik = krawedz->start;
		int sasiad_id = krawedz->koniec;
		int przepustowoscRezydualna = krawedz->waga - krawedz->przeplyw;

		// je¿eli przez kana³ mo¿e przep³yn¹æ oraz nie by³ jeszcze rozpatrzony
		if (przepustowoscRezydualna > 0 && wierzcholki->tablica[sasiad_id]->poprzednik == -1) {
			wierzcholki->tablica[sasiad_id]->poprzednik = poprzednik;

			int aktualnaPrzepustowoscSciezki = wierzcholki->tablica[poprzednik]->klucz;
			wierzcholki->tablica[sasiad_id]->klucz = min(aktualnaPrzepustowoscSciezki, przepustowoscRezydualna);

			if (sasiad_id == graf->wierzcholekKoncowy) {
				delete krawedz;
				delete kolejka;
				return true;
			}

			wstawSasiadow(sasiad_id, kolejka);
		}
		delete krawedz;
	}
	delete kolejka;
	return false;
	
}


