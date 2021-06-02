#pragma once

/*
Okreœla typ reprezentacji grafu w pamiêci
*/
enum class ReprezentacjaGrafu { MACIERZ, LISTA, NONE };

/*
Okresla typ algorytmu.
Wykorzystuje siê go do definiowania liczby wczytaywanych danych z pierwszej linii pliku tekstowego
*/
enum class TypProblemu { MST, SP, MF, DEFAULT };

/*
Okreœla sposób przeszukiwania dla algorytmu Forda-Fulkersona
*/
enum class TrybPrzeszukiwania {BFS, DFS};

/*
Nazwy algorytmów
Wykorzystywane do generowania losowych grafów
*/
enum class TypAlgorytmu { DIJKSTRA, BELLMANFORD, PRIM, KRUSKAL, FORDFURKELSON};

