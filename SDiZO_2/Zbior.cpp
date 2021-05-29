#include "Zbior.h"

Zbior::Zbior(int element) {
	this->element = element;
	this->ranga = 0;
	this->rodzic = this;
}

/*
Zwraca najstarszego rodzica zbioru, czyli identyfikator zbioru
Wywo�anie rekurencyjnie
Po drodze zmniejsza g��bo�� drzewa
Psuje poj�cie rangi, ale jest nadal ona wi�szka b�d� r�wna wysoko�ci drzewa co wystarcza do naszych cel�w
*/
Zbior* Zbior::getIdentyfikator() {
	if (rodzic != this) {
		rodzic = rodzic->getIdentyfikator();
	}
	return rodzic;
}

void Zbior::polaczZbiory(Zbior* zbior1, Zbior* zbior2) {
	if (zbior1->ranga < zbior2->ranga) {
		zbior1->rodzic = zbior2;
	}
	else {
		zbior2->rodzic = zbior1;
	}

	// je�eli drzewa by�y tej samej rangi to ranga zbioru1 rosnie o 1
	if (zbior1->ranga == zbior2->ranga) {
		zbior1->ranga++;
	}
}
