#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#define TASK 3
#define INF INT_MAX
using namespace std;

int mcm(int n, vector<int> &righe) {
  ++n;
  vector<vector<int>> m(n, vector<int>(n, 0));
  for (int delta = 2; delta < n; delta++) {
    for (int i = 1; i < n - delta + 1; i++) {
      int j = i + delta - 1;
      m[i][j] = INF;
      for (int k = i; k < j; k++) {
        int q = m[i][k] + m[k + 1][j] + righe[i - 1] * righe[k] * righe[j];
        // cout << q << endl;
        m[i][j] = min(q, m[i][j]);
      }
      // cout << endl;
    }
  }
#if 0
  for(int i=1;i<n;i++){
    for(int j=1;j<n;j++){
        cout << m[i][j] << "\t";
    }
    cout << endl;
  }
#endif
  return m[1][n - 1];
}

pair<int, int> getMatrixNumbers(string input) {
  input = input.substr(1, input.length() - 2);
  input.replace(input.find('x'), 1, " ");
  //   cout << input << endl;
  string m1, m2;
  stringstream istr(input);
  getline(istr, m1, ' ');
  getline(istr, m2);
  return make_pair(stoi(m1), stoi(m2));
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int n_matrici;
  string matrice;
  vector<int> righe, colonne;
  pair<int, int> matrixpair;
  for (int i = 0; i < TASK; i++) {
    righe.resize(0);
    colonne.resize(0);
    input >> n_matrici;
    for (int j = 0; j < n_matrici; j++) {
      input >> matrice;
      matrixpair = getMatrixNumbers(matrice);
      righe.push_back(matrixpair.first);
      colonne.push_back(matrixpair.second); // bodge!
    }
    righe.push_back(colonne.back());

    output << mcm(n_matrici, righe) << endl;
  }
}