#pragma once
#include<limits>
/*
Struktura danych przechowuj¹ce informacje niezbêdne podczas dzia³ania algorytmów Dijsktry i Bellmana-Forda
*/
class Struktura {
public:
	Struktura();
	int poprzednik;
	int klucz;
	int wierzcholek;
};

