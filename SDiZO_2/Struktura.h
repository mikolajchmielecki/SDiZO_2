#pragma once
#include<limits>
/*
Struktura danych przechowuj�ce informacje niezb�dne podczas dzia�ania algorytm�w Dijsktry i Bellmana-Forda
*/
class Struktura {
public:
	Struktura();
	int poprzednik;
	int klucz;
	int wierzcholek;
};

