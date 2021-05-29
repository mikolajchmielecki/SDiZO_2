#include "SP.h"


/*

*/
string SP::getWynik() {
    string wynik = "Start = ";
    wynik += to_string(graf->wierzcholekStartowy);
    wynik += "\n End\t Dist\t Path\n\n";

    // wpisywanie wynik�w kolejnych wierzcho�k�w
    for (int i = 0; i < graf->liczbaWierzcholkow; i++) {
        string wiersz = " ";
        wiersz += to_string(i);
        wiersz += "\t| ";
        // odleg�o�� od startu
        wiersz += to_string(wierzcholki->tablica[i]->klucz);
        wiersz += "\t|";

        // wy�uskiwanie �cie�ki do danego wierzcho�ka
        string sciezka = "";
        int wierzcholek = i;
        while (wierzcholek != graf->wierzcholekStartowy) {
            sciezka += to_string(wierzcholek);
            sciezka += " ";
            wierzcholek = wierzcholki->tablica[wierzcholek]->poprzednik;

            // je�eli graf jest niesp�jny to poprzednik, kt�rego wierzcho�ka b�dzie wynosi� -1
            if (wierzcholek == -1) {
                throw exception("[ERROR] Graf jest niesp�jny");
            }
        }
        // dodanie wierzcho�ka startowego
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


