#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <utility>
#include <vector>
#define TASK 100
#define INF INT_MAX
int decreaseKey;
using namespace std;

// per brevità si dispongono le classi nel file del main

template <typename T> class HashTable {
public:
  vector<int> table;
  int size;

  HashTable(int s) : size(s) { table.resize(s, INT_MAX); }

  int hash(int key) { return fmod(key, size); }

  void insert(int key) {
    int index = hash(key);
    while (table[index] != INT_MAX) {
      index = (index + 1) % size;
    }
    table[index] = key;
  }

  int search(int key) {
    int index = hash(key);
    while (table[index] != INT_MAX) {
      if (table[index] == key)
        return index;
      index = (index + 1) % size;
    }
    return -1;
  }
  float getAlpha() {
    int count = 0;
    for (auto &el : table)
      count += (el != INT_MAX);
    return (float)count / size;
  }
};

// template <class T> class HashTable {
// public:
//   list<T> *table;
//   int size;  // numero di nodi occupati
//   int slots; // numero di posti occupabili
//   int hash(T key) {
//     // return key % this->slots;
//     return fmod(key, slots);
//   }

//   int getSize() { return this->size; }
//   int getSlots() { return this->slots; }
//   HashTable<T>(int _slots) {
//     this->slots = _slots;
//     this->size = 0;
//     table = new list<T>[this->slots];
//   }
//   HashTable<T>(int _slots, int _size, T *data) {
//     this->slots = _slots;
//     table = new list<T>[this->slots];
//     for (int i = 0; i < _size; i++) {
//       this->insertKey(data[i]);
//     }
//   }
//   HashTable<T> *insertKey(T key) {
//     table[hash(key)].push_back(key);
//     ++size;
//     return this;
//   }
//   void print() {
//     for (int i = 0; i < this->slots; i++) {
//       for (auto &el : table[i])
//         cout << el << " ";
//       cout << "\n";
//     }
//   }
// };

template <class T> class Grafo {
  typedef pair<int, T> paio;
  map<T, vector<pair<T, int>>> nodi;

public:
  void addNodo(T nodo) { nodi[nodo] = vector<pair<T, int>>(); }
  void addArco(T sorgente, T destinazione, int peso) {
    nodi[sorgente].push_back(make_pair(destinazione, peso));
  }
  map<T, int> dijkstra(T sorgente, T destinazione, HashTable<int> &table) {
    map<T, int> cammini_minimi; // mappa finale di cammini minimi (S)
    for (auto &nodo : nodi)
      cammini_minimi[nodo.first] = INF;
    cammini_minimi[sorgente] = 0;
    priority_queue<paio, vector<paio>, greater<paio>> heap;
    heap.push(make_pair(0, sorgente));
    while (heap.size() > 0) {
      T u = heap.top().second;
      heap.pop();
      for (auto &v : nodi[u]) {
        if (cammini_minimi[v.first] >= cammini_minimi[u] + v.second) {
          if (decreaseKey == INF)
            decreaseKey = 0;
          ++decreaseKey; // d[v] > d[u] + m(u, v)
          cammini_minimi[v.first] = cammini_minimi[u] + v.second;
          heap.push(make_pair(cammini_minimi[v.first], v.first));
        }
      }
    }
    for (auto &el : cammini_minimi) {
      table.insert(el.second);
    }

    return cammini_minimi;
  }
};

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int num_nodi, num_archi;
  string type, temp;
  string nodosorgente, nododestinazione;
  int pesoarco;
  char parentesi;
  Grafo<string> grafo;
  string sorgente, destinazione;
  for (int i = 0; i < TASK; i++) {
    grafo = Grafo<string>();

    decreaseKey = INF;
    input >> num_nodi >> num_archi >> type;
    HashTable<int> tabella = HashTable<int>(num_archi);
    for (int j = 0; j < num_nodi; j++) {
      input >> temp;
      grafo.addNodo(temp);
    }
    for (int j = 0; j < num_archi; j++) {
      input >> parentesi >> nodosorgente >> nododestinazione >> pesoarco >>
          parentesi;
      grafo.addArco(nodosorgente, nododestinazione, pesoarco);
    }
    input >> sorgente >> destinazione;
    auto mappa = grafo.dijkstra(sorgente, destinazione, tabella);
    output << tabella.search(mappa[destinazione]) << " " << decreaseKey << endl;
    if (mappa.size() != num_nodi) {
      cerr << "VIOLAZIONE CONSISTENZA " <<mappa.size() << " != "<<num_nodi << endl;
      exit(1);
    }
    cout << "***Task " << i + 1 << " | Alfa " << tabella.getAlpha() << " ("
         << round(tabella.getAlpha() * 100) << "%)" << endl;
    cout << "Numero nodi riportato da mappa dijkstra: " << mappa.size() << " "
         << " | Numero archi da input: " << num_archi << "***" << endl;
  }
}