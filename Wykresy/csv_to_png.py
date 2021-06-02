import os
import matplotlib.pyplot as plt
import csv
import numpy as np
import math

"""
Wczytywanie plików csv z danymi
"""
sciezka = os.getcwd()
listaPlikow = []
for root, dirs, files in os.walk(sciezka):
    for file in files:
        if file.endswith(".csv"):
             listaPlikow.append(os.path.join(root, file))

#print(listaPlikow)

print("Autor: Mikołaj Chmielecki")
print("Generowanie wykresów na podstawie plików csv z aktualnego katalogu...")

"""
Generowanie wykresu dla każdego pliku z danymi
"""
for plik in listaPlikow:

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
    jednostka = "µs"
    if  max(czasOperacji) > 999:
        nowaLista = [x/1000 for x in czasOperacji]
        czasOperacji = nowaLista[:]
        jednostka = "ms"
    if max(czasOperacji) > 999:
        nowaLista = [x/1000 for x in czasOperacji]
        czasOperacji = nowaLista[:]
        jednostka = "s"

    plt.plot(liczbaElemetnow, czasOperacji, marker='o')
    plt.xlabel('Liczba elementów')
    plt.ylabel(f'Czas operacji [{jednostka}]')
    plt.xticks(rotation=45, ha="right")

    plt.ticklabel_format(useOffset=False, style='plain')
    plt.title(nazwa)
    plt.tight_layout()
    plt.savefig(plik.replace('.csv', '.png'), dpi=500)
    plt.close()

    fig = plt.figure(dpi=250)
    ax = fig.add_subplot(1, 1, 1)
    table_data = []
    for i in range(len(liczbaElemetnow)):
        table_data.append([liczbaElemetnow[i], round(czasOperacji[i], 3 - int(math.floor(math.log10(abs(czasOperacji[i])))) - 1)
])

    ccolors = plt.cm.BuPu(np.full(2, 0.1))
    table = ax.table(cellText=table_data, colColours=ccolors,
                     colLabels=['Liczba elementów', f'Czas operacji [{jednostka}]'], loc='center')
    table.set_fontsize(14)
    table.scale(1, 2)
    plt.title(nazwa)
    ax.axis('off')

    plt.tight_layout()
    plt.savefig(str(plik.replace('.csv', '_tabela.png')))
    plt.close()

print("Generowanie zakończone")
