import os
import matplotlib.pyplot as plt
import csv
import numpy as np
import math
import unicodedata

problemy = ["MST", "SP", "MF"]
algorytmy = {
    "MF": ["Ford-Fulkerson-BFS", "Ford-Fulkerson-DFS"],
    "MST": ["Kruskal", "Prim"],
    "SP": ["Dijkstra", "Bellman-Ford"]
}


"""
Wczytywanie plików csv z danymi
"""
sciezka = os.getcwd()
listaPlikow = []
for root, dirs, files in os.walk(sciezka+'\\Dane\\'):
    for file in files:
        if file.endswith(".csv"):
             listaPlikow.append(os.path.join(root, file))

#print(listaPlikow)

print("Autor: Mikołaj Chmielecki")
print("Generowanie wykresów na podstawie plików csv z aktualnego katalogu...")

listaListDanych = []
listaTytulow = []
"""
Tworzenie listy list plików do każdego wykresu
"""
nrProblemu = 0
for problem in problemy:
    for i in range(6):
        listaListDanych.append([])
    listaTytulow.append(problem + " - macierz sąsiedztwa")
    listaTytulow.append(problem + " - lista sąsiedztwa")
    listaTytulow.append(problem + " - gęstość 25%")
    listaTytulow.append(problem + " - gęstość 50%")
    listaTytulow.append(problem + " - gęstość 75%")
    listaTytulow.append(problem + " - gęstość 99%")
    for plik in listaPlikow:
        head, tail = os.path.split(plik)
        plikName = tail
        if (algorytmy[problem][0] in plikName or algorytmy[problem][1] in plikName):
            if "macierz" in plik:
                listaListDanych[nrProblemu*6].append(plik)
            if "lista" in plik:
                listaListDanych[nrProblemu*6+1].append(plik)
            if "25" in plik:
                listaListDanych[nrProblemu*6+2].append(plik)
            if "50" in plik:
                listaListDanych[nrProblemu*6+3].append(plik)
            if "75" in plik:
                listaListDanych[nrProblemu*6+4].append(plik)
            if "99" in plik:
                listaListDanych[nrProblemu*6+5].append(plik)

    nrProblemu += 1



"""
Generowanie wykresu dla każdego pliku z danymi
"""
licznikWykresu = 0
for lista in listaListDanych:
    plt.close()
    plt.title(listaTytulow[licznikWykresu])


    for plik in lista:

        liczbaElemetnow = []
        czasOperacji = []
        nazwa = ""
        """
        Otwieranie pliku z danymi
        """
        with open(plik, 'r') as csvfile:
            plots = csv.reader(csvfile, delimiter=';')
            i = 0
            """
            Czytanie kolejnych wierszy
            """
            for row in plots:
                if i == 0:
                    nazwa = row[0]
                else:
                    liczbaElemetnow.append(int(row[0]))
                    czasOperacji.append(float(row[1].replace(',', '.')))
                i += 1

        nowaLista = [x / 1000 for x in czasOperacji]
        czasOperacji = nowaLista[:]
        jednostka = "ms"
        """
        jednostka = "µs"
        if  max(czasOperacji) > 999:
            nowaLista = [x/1000 for x in czasOperacji]
            czasOperacji = nowaLista[:]
            jednostka = "ms"
        if max(czasOperacji) > 999:
            nowaLista = [x/1000 for x in czasOperacji]
            czasOperacji = nowaLista[:]
            jednostka = "s"
        """


        plt.plot(liczbaElemetnow, czasOperacji, marker='o', label=nazwa)
        plt.xticks(liczbaElemetnow)
        plt.xlabel('Liczba elementów')
        plt.ylabel(f'Czas operacji [{jednostka}]')

    #plt.ticklabel_format(useOffset=False, style='plain')
    plt.legend()
    plt.tight_layout()
    normalize = unicodedata.normalize('NFD', listaTytulow[licznikWykresu]).encode('ascii', 'ignore')
    plt.savefig("Dane/" + str(normalize).replace("b\'","").replace("\'","").replace("%","") + ".pdf" )
    plt.close()
    licznikWykresu += 1

print("Generowanie zakończone")
