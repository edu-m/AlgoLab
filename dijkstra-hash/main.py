class Nodo:
    def __init__(self, chiave):
        self.chiave = chiave
        self.adiacenti = {}

    def aggiungi_arco(self, nodo_destinazione, peso):
        self.adiacenti[nodo_destinazione] = peso

class Grafo:
    def __init__(self):
        self.nodi = {}

    def aggiungi_nodo(self, chiave):
        self.nodi[chiave] = Nodo(chiave)

    def aggiungi_arco(self, sorgente, destinazione, peso):
        if sorgente not in self.nodi:
            self.aggiungi_nodo(sorgente)
        if destinazione not in self.nodi:
            self.aggiungi_nodo(destinazione)
        self.nodi[sorgente].aggiungi_arco(self.nodi[destinazione], peso)

import heapq

def dijkstra(grafo, sorgente):
    distanze = {nodo: float('infinity') for nodo in grafo.nodi}
    distanze[sorgente] = 0
    coda_priorita = [(0, sorgente)]
    chiamate_decrease_key = 0

    while coda_priorita:
        dist_corrente, nodo_corrente = heapq.heappop(coda_priorita)
        if dist_corrente > distanze[nodo_corrente]:
            continue
        for adiacente, peso in grafo.nodi[nodo_corrente].adiacenti.items():
            distanza_alternativa = dist_corrente + peso
            if distanza_alternativa < distanze[adiacente.chiave]:
                distanze[adiacente.chiave] = distanza_alternativa
                heapq.heappush(coda_priorita, (distanza_alternativa, adiacente.chiave))
                chiamate_decrease_key += 1

    return distanze, chiamate_decrease_key

class HashTable:
    def __init__(self, dimensione):
        self.tabella = [None] * dimensione
        self.dimensione = dimensione

    def _funzione_hash(self, chiave):
        return chiave % self.dimensione

    def inserisci(self, chiave):
        indice = self._funzione_hash(chiave)
        while self.tabella[indice] is not None and self.tabella[indice] != chiave:
            indice = (indice + 1) % self.dimensione
        self.tabella[indice] = chiave

    def ricerca(self, chiave):
        indice = self._funzione_hash(chiave)
        while self.tabella[indice] is not None:
            if self.tabella[indice] == chiave:
                return indice
            indice = (indice + 1) % self.dimensione
        return -1

with open("input.txt", "r") as infile, open("output.txt", "w") as outfile:
    for linea in infile:
        parti = linea.strip().split()
        N, M = int(parti[0]), int(parti[1])
        tipo_dato = parti[2]
        nodi = parti[3:3+N]
        archi = parti[3+N:3+N+3*M]
        nodo_sorgente, nodo_destinazione = parti[-2], parti[-1]

        grafo = Grafo()
        for i in range(0, 10):
            print(len(archi))
            grafo.aggiungi_arco(archi[i][1:-1], archi[i+1][:-1], int(archi[i+2][1:-1]))

        distanze, chiamate = dijkstra(grafo, nodo_sorgente)

        tabella = HashTable(M)
        distanza_destinazione = int(distanze[nodo_destinazione]) if nodo_destinazione in distanze else float('inf')
        tabella.inserisci(distanza_destinazione)
        indice_tabella = tabella.ricerca(distanza_destinazione)

        outfile.write(f"{indice_tabella} {chiamate}\n")
