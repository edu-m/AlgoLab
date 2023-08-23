#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#define TASK 1
#define INF 1001

int calcolaResto(int R, int N, const vector<int> &tagli) {
  vector<vector<int>> matrix(N + 1, vector<int>(R + 1, INF));
  for (int i = 0; i <= N; ++i) // inizializzo tutta la prima colonna a 0
    matrix[i][0] = 0;
  for (int i = 1; i <= N; ++i) // scorro per ciascun taglio disponibile ogni
                               // numero fino ad arrivare al resto
    for (int j = 1; j <= R; ++j)
      if (j >= tagli[i - 1])
        matrix[i][j] = min(1 + matrix[i][j - tagli[i - 1]], matrix[i - 1][j]);
      else
        matrix[i][j] = matrix[i - 1][j];
  return matrix[N][R];
}

int main() {
  int R, N;
  vector<int> tagli;
  ifstream input("input.txt");
  ofstream output("output.txt");
  for (int i = 0; i < TASK; i++) {
    input >> R >> N;
    tagli.resize(N);
    for (int i = 0; i < N; ++i)
      input >> tagli[i];
    output << calcolaResto(R, N, tagli) << endl;
  }
}