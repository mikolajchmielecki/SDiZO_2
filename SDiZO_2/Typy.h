#pragma once

/*
Okre�la typ reprezentacji grafu w pami�ci
*/
enum class ReprezentacjaGrafu { MACIERZ, LISTA, NONE };

/*
Okresla typ algorytmu.
Wykorzystuje si� go do definiowania liczby wczytaywanych danych z pierwszej linii pliku tekstowego
*/
enum class TypProblemu { MST, SP, MF, DEFAULT };

/*
Okre�la spos�b przeszukiwania dla algorytmu Forda-Fulkersona
*/
enum class TrybPrzeszukiwania {BFS, DFS};

/*
Nazwy algorytm�w
Wykorzystywane do generowania losowych graf�w
*/
enum class TypAlgorytmu { DIJKSTRA, BELLMANFORD, PRIM, KRUSKAL, FORDFURKELSON};

