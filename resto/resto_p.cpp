#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#define TASK 100
#define INF 1001

void printUsedCoins(ofstream &output, const vector<vector<int>> &matrix,
                    const vector<int> &coins, int N, int R) {
  vector<int> monete;
  int i = N, j = R;
  while (i > 0 && j > 0)
    if (matrix[i][j] == 1 + matrix[i][j - coins[i - 1]]) {
      monete.push_back(coins[i - 1]);
      j -= coins[i - 1];
    } else
      --i;
  output << matrix[N][R] << " ";
  sort(monete.begin(), monete.end());
  for (int i = 0; i < monete.size(); i++)
    output << monete[i] << " ";
  output << endl;
}

void calcolaResto(ofstream &output, int R, int N, const vector<int> &tagli) {
  vector<vector<int>> matrix(N + 1, vector<int>(R + 1, INF));
  for (int i = 0; i <= N; ++i) // inizializzo tutta la prima colonna a 0
    matrix[i][0] = 0;
  for (int i = 1; i <= N; ++i) // scorro per ciascun taglio disponibile ogni
                               // numero fino ad arrivare al R
    for (int j = 1; j <= R; ++j)
      if (j >= tagli[i - 1])
        matrix[i][j] = min(1 + matrix[i][j - tagli[i - 1]], matrix[i - 1][j]);
      else
        matrix[i][j] = matrix[i - 1][j];

  printUsedCoins(output, matrix, tagli, N, R);
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
    sort(tagli.begin(), tagli.end(), greater<int>());
    calcolaResto(output, R, N, tagli);
  }
}