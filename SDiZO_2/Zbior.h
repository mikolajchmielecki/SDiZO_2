#pragma once
class Zbior {
public:
	Zbior(int element);
	int ranga;
	Zbior* rodzic;
	int element;
	Zbior* getIdentyfikator();
	static void polaczZbiory(Zbior* zbior1, Zbior* zbior2);

};

