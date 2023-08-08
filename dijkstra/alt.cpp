#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#define TASK 100
#define INF INT_MAX
using namespace std;

template <class T> class Grafo {
  typedef pair<int, T> paio;
  map<T, vector<pair<T, int>>> nodi;

public:
  void addNodo(T nodo) { nodi[nodo] = vector<pair<T, int>>(); }
  void addArco(T sorgente, T destinazione, int peso) {
    nodi[sorgente].push_back(make_pair(destinazione, peso));
  }
  map<T, int> dijikstra(T sorgente) {
    map<T, int> cammini_minimi; // mappa finale di cammini minimi (S)
    for (auto &nodo : nodi)
      cammini_minimi[nodo.first] = INF;
    cammini_minimi[sorgente] = 0;
    priority_queue<paio, vector<paio>, greater<paio>>
        heap; // heap temporaneo per algoritmo (Q)
    heap.push(make_pair(0, sorgente));
    while (heap.size() > 0) {
      T u = heap.top().second;
      heap.pop();
      for (auto &v : nodi[u]) {
        if (cammini_minimi[v.first] >
            cammini_minimi[u] + v.second) { // d[v] > d[u] + m(u, v)
          cammini_minimi[v.first] = cammini_minimi[u] + v.second;
          heap.push(make_pair(cammini_minimi[v.first], v.first));
        }
      }
    }
    return cammini_minimi;
  }
};

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int nodi, archi;
  string type;
  string nodo;
  string arcosorgente, arcodestinazione, arcopeso;
  string sorgente, destinazione;

  for (int i = 0; i < TASK; i++) {
    input >> nodi >> archi >> type;
    Grafo<string> grafo;
    for (int i = 0; i < nodi; i++) {
      input >> nodo;
      grafo.addNodo(nodo);
    }
    for (int i = 0; i < archi; i++) {
      input >> arcosorgente >> arcodestinazione >> arcopeso;
      arcosorgente = arcosorgente.substr(1, arcosorgente.length());
      arcopeso = arcopeso.substr(0, arcopeso.length() - 1);
      grafo.addArco(arcosorgente, arcodestinazione, stoi(arcopeso));
    }
    input >> sorgente >> destinazione;
    auto cammini_minimi = grafo.dijikstra(sorgente);
    output << cammini_minimi[destinazione] << endl;
  }
}
