#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T> class Graph {
public:
  unordered_map<T, vector<pair<T, int>>> adj;
  void addNode(T u) { adj[u] = vector<pair<T, int>>(); }
  void addEdge(T u, T v, int wt) { adj[u].push_back({v, wt}); }
};

class OpenAddressingHashTable {
public:
  vector<int> table;
  int size;

  OpenAddressingHashTable(int s) : size(s) { table.resize(s, INT_MAX); }

  int hashFunction(int key) { return key % size; }

  void insert(int key) {
    int index = hashFunction(key);
    while (table[index] != INT_MAX) {
      index = (index + 1) % size;
    }
    table[index] = key;
  }

  int search(int key) {
    int index = hashFunction(key);
    while (table[index] != INT_MAX) {
      if (table[index] == key)
        return index;
      index = (index + 1) % size;
    }
    return -1;
  }
};

template <typename T>
unordered_map<T, int> dijkstra(Graph<T> &g, T src, T dest, OpenAddressingHashTable &hashTable,
              int &decreaseKeyCount) {
  unordered_map<T, int> dist;
  for (auto &j : g.adj) {
    dist[j.first] = INT_MAX;
  }

  priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;

  pq.push({0, src});
  dist[src] = 0;

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    for (auto &i : g.adj[u]) {
      auto [v, wt] = i;

      if (dist[v] > dist[u] + wt) {
        dist[v] = dist[u] + wt;
        pq.push({dist[v], v});
        ++decreaseKeyCount;
      }
    }
  }

  int index = (dist[dest] == INT_MAX) ? INT_MAX : (int)dist[dest];
  hashTable.insert(index);
  return dist;
}

int main() {
  ifstream infile("input.txt");
  ofstream outfile("output.txt");
  string line;

  while (getline(infile, line)) {
    istringstream iss(line);
    int N, M;
    string type;
    iss >> N >> M >> type;

    Graph<string> g = Graph<string>();
    OpenAddressingHashTable hashTable(M);

    for (int i = 0; i < N; ++i) {
      string node;
      iss >> node;
    //   cout << node << endl;
      g.addNode(node);
    }

    for (int i = 0; i < M; ++i) {
      string u, v;
      int wt;
      char dummy;
      iss >> dummy >> u >> v >> wt >> dummy;
      g.addEdge(u, v, wt);
    }

    string src, dest;
    iss >> src >> dest;

    int decreaseKeyCount = 0;
    auto dist = dijkstra(g, src, dest, hashTable, decreaseKeyCount);

    int index = hashTable.hashFunction(dist[dest]);
    outfile << index << " " << decreaseKeyCount << endl;
  }

  infile.close();
  outfile.close();
  return 0;
}
