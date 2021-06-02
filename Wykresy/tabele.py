import os
import matplotlib.pyplot as plt
import csv
import numpy as np
import math



algorytmy = ["Kruskal", "Prim", "Dijkstra","Bellman-Ford", "Ford-Fulkerson-BFS", "Ford-Fulkerson-DFS"]


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

"""
Generowanie wykresu dla każdego problemu
"""
for algorytm in algorytmy:
    columns = ["Liczba\nwierzchołków"]
    wartosci = []
    pierwszy = True
    licznik = 0
    for plik in listaPlikow:
        if algorytm in plik:
            liczbyWierzcholkow = []
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
                        liczbyWierzcholkow.append(int(row[0]))
                        czasOperacji.append(float(row[1].replace(',', '.')))
                    i += 1
            jednostka = "µs"
            if max(czasOperacji) > 999:
                nowaLista = [x / 1000 for x in czasOperacji]
                czasOperacji = nowaLista[:]
                jednostka = "ms"
            if max(czasOperacji) > 999:
                nowaLista = [x / 1000 for x in czasOperacji]
                czasOperacji = nowaLista[:]
                jednostka = "s"

            columns.append(nazwa.replace(algorytm,"") + f"\n[{jednostka}]")

            if pierwszy:
                i = 0
                for liczba in liczbyWierzcholkow:
                    wartosci.append([])
                    wartosci[i].append(liczba)
                    i += 1
            i = 0
            for czas in czasOperacji:
                wartosci[i].append(round(czasOperacji[i], 3 - int(math.floor(math.log10(abs(czasOperacji[i])))) - 1))
                i += 1
            pierwszy = False
            licznik += 1

    if licznik==0:
        continue

    # generowanie tabeli dla kazdego problemu

    #fig = plt.figure(dpi=250)
    fig = plt.figure(figsize=(10,3))
    ax = fig.add_subplot(1, 1, 1)


    ccolors = plt.cm.BuPu(np.full(len(columns), 0.1))
    table = ax.table(cellText=wartosci, colColours=ccolors,
                     colLabels=columns, loc='center')

    cellDict = table.get_celld()
    for i in range(0, len(columns)):
        cellDict[(0, i)].set_height(.3)

    plt.title(algorytm)
    table.auto_set_column_width(col=list(range(len(columns))))
    ax.axis('off')
    plt.tight_layout()
    plt.savefig("Dane/" +algorytm+'_tabela.pdf')
    plt.close()

print("Generowanie zakończone")
