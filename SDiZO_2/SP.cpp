#include "SP.h"


/*

*/
string SP::getWynik() {
    string wynik = "Start = ";
    wynik += to_string(graf->wierzcholekStartowy);
    wynik += "\n End\t Dist\t Path\n\n";

    // wpisywanie wyników kolejnych wierzcho³ków
    for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
        string wiersz = " ";
        wiersz += to_string(i);
        wiersz += "\t| ";
        // odleg³oœæ od startu
        wiersz += to_string(wierzcholki->tablica[i]->klucz);
        wiersz += "\t|";

        // wy³uskiwanie œcie¿ki do danego wierzcho³ka
        string sciezka = "";
        int wierzcholek = i;
        while (wierzcholek != graf->wierzcholekStartowy) {
            sciezka += to_string(wierzcholek);
            sciezka += " ";
            wierzcholek = wierzcholki->tablica[wierzcholek]->poprzednik;

            // je¿eli graf jest niespójny to poprzednik, którego wierzcho³ka bêdzie wynosi³ -1
            if (wierzcholek == -1) {
                throw exception("[ERROR] Graf jest niespójny");
            }
        }
        // dodanie wierzcho³ka startowego
        sciezka += to_string(wierzcholek);
        sciezka += " ";

        sciezka = odwrocString(sciezka);
        wiersz += sciezka;
        wiersz += "\n";
        wynik += wiersz;

    }
    return wynik;
}

string SP::odwrocString(string wejscie) {
    int len = wejscie.length();
    int n = len - 1;
    for (int i = 0; i < (len / 2); i++) {
        swap(wejscie[i], wejscie[n]);
        n--;
    }
    return wejscie;
}


