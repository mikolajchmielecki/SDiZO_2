#pragma once
#include "MySTL.h"
#include"Typy.h"
#include "Krawedz.h"

/*
Klasa implementuj¹ca kolejkê LIFO lub FIFO zale¿nie od parametry tryb
Wykorzystywana do przeszukiwanai wg³¹d i wrzesz
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

