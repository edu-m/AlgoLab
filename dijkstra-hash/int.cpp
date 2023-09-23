#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#define TASK 100

using namespace std;

template <typename T> class Grafo {
public:
  unordered_map<T, vector<pair<T, int>>> adj;
  void addNode(T u) { adj[u] = vector<pair<T, int>>(); }
  void addEdge(T u, T v, int w) { adj[u].push_back({v, w}); }

  int dijkstra(T start, T end, int &decreaseKeyCalls) {
    unordered_map<T, int> dist;
    for(auto &node : adj)
        dist[node.first] = 30000;
    priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>>
        pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
      int d = pq.top().first;
      T u = pq.top().second;
      pq.pop();

      for (auto &neighbour : adj[u]) {
        T v = neighbour.first;
        int weight = neighbour.second;

        if (dist[v] > dist[u] + weight) {
          dist[v] = dist[u] + weight;
          pq.push({dist[v], v});
          decreaseKeyCalls++;
        }
      }
    }

    // if (dist.find(end) == dist.end()) return INT_MAX;
    return dist[end];
  }
};

int linearProbingHash(int *table, int size, int key) {
  // cout << size << " " << key << endl;
  int h = key % size;
  while (table[h] != -1) {
    h = (h + 1) % size;
  }
  table[h] = key;
  return h;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int decreaseKeyCalls;

  for (int t = 0; t < TASK; ++t) {
    int N, M;
    string type;
    input >> N >> M >> type;

    Grafo<string> g; // assume type = "int" for simplicity
    int hashTable[M];
    for (int i = 0; i < M; ++i)
      hashTable[i] = -1;
    string node;
    for (int i = 0; i < N; ++i) {

      input >> node;
    //   cout << "node: " << node << endl;
      g.addNode(node);
    }
  string u, v; int w;
  char delim;
    for (int i = 0; i < M; ++i) {
    
      input >> delim >> u >> v >> w >> delim;
      g.addEdge(u, v, w);
    }

    string start, end;
    input >> start >> end;

    decreaseKeyCalls = 0;
    cout << start << " " << end << endl;
    int minDist = g.dijkstra(start, end, decreaseKeyCalls);
    int hashIndex = linearProbingHash(hashTable, M, minDist);
    cout << minDist << endl;
    output << hashIndex << " " << decreaseKeyCalls << endl;
  }

  return 0;
}
