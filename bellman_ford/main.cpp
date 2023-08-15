#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;
#define TASK 1
#define INF INT_MAX

template <class T> class Grafo {
  typedef pair<int, T> paio;
  map<T, vector<pair<T, int>>> nodi;

public:
  void addNodo(T nodo) { nodi[nodo] = vector<pair<T, int>>(); }
  void addArco(T sorgente, T destinazione, int peso) {
    nodi[sorgente].push_back(make_pair(destinazione, peso));
  }
  void bellman_ford(T sorgente, int n_archi, int n_nodi) {
    map<T, int> cammini_minimi;

    for (const auto &nodo : nodi) {
      cammini_minimi[nodo.first] = INF;
    }
    cammini_minimi[sorgente] = 0;
    for (int i = 0; i < n_archi; i++) {
        for(int j=0;j<n_nodi;j++){
            
        }
    }
  }
};

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  Grafo<string> grafo;
  int nodi, archi;
  string type, nodo;
  string arcosorgente, arcodestinazione, arcopeso;
  string sorgente, destinazione;
  for (int i = 0; i < TASK; i++) {
    input >> nodi >> archi >> type;
    for (int j = 0; j < nodi; j++) {
      input >> nodo;
      cout << "aggiungo nodo: " << nodo << endl;
      grafo.addNodo(nodo);
    }
    for (int j = 0; j < archi; j++) {
      input >> arcosorgente >> arcodestinazione >> arcopeso;
      grafo.addArco(arcodestinazione.substr(1, arcodestinazione.length() - 1),
                    arcodestinazione,
                    stoi(arcopeso.substr(0, arcopeso.length() - 1)));
    }
    input >> sorgente >> destinazione;
    grafo.bellman_ford(sorgente, archi, nodi);
    // output << cammini_minimi[destinazione] << endl;
  }
}