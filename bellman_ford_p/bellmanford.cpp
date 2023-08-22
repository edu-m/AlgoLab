#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#define INF 101
#define TASK 100

using namespace std;

template <class T> class Grafo {
  typedef pair<T, int> paio;
  map<T, vector<paio>> grafo;

  // grafo[sorgente][2].first

public:
  void addNodo(T value) {
    if (grafo[value].empty())
      grafo[value] = vector<paio>();
  }
  void addArco(T sorgente, T arcodestinazione, int peso) {
    grafo[sorgente].push_back(make_pair(arcodestinazione, peso));
  }
  void printGrafo() {
    for (auto &el : grafo)
      for (int i = 0; i < el.second.size(); i++)
        cout << el.first << " " << el.second[i].first << " "
             << el.second[i].second << endl;
  }

  int trova_peso(T sorgente, T destinazione) {
    vector<paio> lista = grafo[sorgente];
    for (int i = 0; i < lista.size(); i++)
      if (lista[i].first == destinazione)
        return lista[i].second;
    return INF;
  }

  map<T, int> bellman_ford(T sorgente, int n_archi, int n_nodi,
                           int max_iterations) {
    // cout << "sorgente: " << sorgente << endl;
    map<T, int> cammini_minimi;
    for (auto &el : grafo)
      cammini_minimi[el.first] = INF;
    cammini_minimi[sorgente] = 0;
    for (int i = 0; i < max_iterations; i++)
      for (auto &u : cammini_minimi)
        for (auto &v : cammini_minimi)
          if (v.second > u.second + trova_peso(u.first, v.first))
            v.second = u.second + trova_peso(u.first, v.first);

    return cammini_minimi;
  }
};

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int n_nodi;
  int n_archi;
  int max_iterations;
  string node, arcosorgente, arcodestinazione, weight, sorgente, destinazione;
  Grafo<string> grafo;

  for (int i = 0; i < TASK; i++) {
    input >> n_nodi >> n_archi >> max_iterations;
    grafo = Grafo<string>();

    for (int j = 0; j < n_archi; j++) {
      input >> arcosorgente >> arcodestinazione >> weight;
      // cout << arcosorgente.substr(1, arcosorgente.length() - 1) << " ";
      grafo.addNodo(arcosorgente.substr(1, arcosorgente.length() - 1));
      grafo.addArco(arcosorgente.substr(1, arcosorgente.length() - 1),
                    arcodestinazione,
                    stoi(weight.substr(0, weight.length() - 1)));
    }

    input >> sorgente >> destinazione;
    // cout << "sorgente input: " << sorgente << endl;
    auto res = grafo.bellman_ford(sorgente, n_archi, n_nodi, max_iterations);
    if (res[destinazione] == INF)
      output << "inf." << endl;
    else
      output << res[destinazione] << endl;
  }
}