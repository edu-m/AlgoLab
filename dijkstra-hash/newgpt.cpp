#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T> class Grafo {
public:
  unordered_map<T, vector<pair<T, int>>> adj;
  void addNode(T u) { adj[u] = vector<pair<T, int>>(); }
  void addEdge(T u, T v, int w) { adj[u].push_back({v, w}); }
};

template <typename T>
int dijkstra(Grafo<T> &g, T start, T end, int &decreaseKeyCalls) {
  unordered_map<T, int> dist;
  priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
  pq.push({0, start});
  dist[start] = 0;

  while (!pq.empty()) {
    int d = pq.top().first;
    T u = pq.top().second;
    pq.pop();

    for (auto &neighbour : g.adj[u]) {
      T v = neighbour.first;
      int weight = neighbour.second;

      if (dist.find(v) == dist.end() || dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
        decreaseKeyCalls++;
      }
    }
  }

  if (dist.find(end) == dist.end())
    return INT_MAX;
  return dist[end];
}

int linearProbingHash(int *table, int size, int key) {
  int h = key % size;
  while (table[h] != -1) {
    h = (h + 1) % size;
  }
  table[h] = key;
  return h;
}

int main() {
  int tasks = 100;
  int decreaseKeyCalls;
  ifstream input("input.txt");
  ofstream output("output.txt");
  for (int t = 0; t < tasks; ++t) {
    int N, M;
    string type;
    input >> N >> M >> type;

    Grafo<string> g;
    int hashTable[M];
    for (int i = 0; i < M; ++i)
      hashTable[i] = -1;
    string node;
    for (int i = 0; i < N; ++i) {

      input >> node;
      g.addNode(node);
    }
    string u, v;
    int w;
    for (int i = 0; i < M; ++i) {

      input >> u >> v >> w;
      g.addEdge(u, v, w);
    }

    string start, end;
    input >> start >> end;

    decreaseKeyCalls = 0;
    int minDist = dijkstra(g, start, end, decreaseKeyCalls);
    int hashIndex = linearProbingHash(hashTable, M, minDist);

    output << hashIndex << " " << decreaseKeyCalls << endl;
  }

  return 0;
}
