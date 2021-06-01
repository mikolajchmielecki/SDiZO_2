#pragma once
#include "MySTL.h"
#include"Typy.h"
#include "Krawedz.h"

/*
Klasa implementuj�ca kolejk� LIFO lub FIFO zale�nie od parametry tryb
Wykorzystywana do przeszukiwanai wg��d i wrzesz
*/
class Kolejka {
public:
	Kolejka(TrybPrzeszukiwania tryb);
	~Kolejka();
	void push(Krawedz* wierzcholek);
	Krawedz* pop();
	bool czyPusta();
private:
	Lista<Krawedz*>* lista;
	TrybPrzeszukiwania tryb;
};

