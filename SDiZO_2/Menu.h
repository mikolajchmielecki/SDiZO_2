#pragma once
#include <string>
using namespace std;
class Menu {
public:
	Menu(int, string*, string);
	int wyswietl();
	bool czyUruchomione();
private:
	string menuString;
	int liczbaOpcji;
	bool uruchomione;
};

