// See the Cormen book for details of the
// following algorithm
#include <bits/stdc++.h>
using namespace std;
#define TASK 3
// Matrix Ai has dimension p[i-1] x p[i]
// for i = 1..n
int MatrixChainOrder(vector<int> p, int n) {

  /* For simplicity of the program, one
  extra row and one extra column are
  allocated in m[][]. 0th row and 0th
  column of m[][] are not used */
  int m[n][n];

  int i, j, k, L, q;

  /* m[i, j] = Minimum number of scalar
  multiplications needed to compute the
  matrix A[i]A[i+1]...A[j] = A[i..j] where
  dimension of A[i] is p[i-1] x p[i] */

  // cost is zero when multiplying
  // one matrix.
  for (i = 1; i < n; i++)
    m[i][i] = 0;

  // L is chain length.
  for (L = 2; L < n; L++) {
    for (i = 1; i < n - L + 1; i++) {
      j = i + L - 1;
      m[i][j] = INT_MAX;
      for (k = i; k <= j - 1; k++) {
        // q = cost/scalar multiplications
        q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (q < m[i][j])
          m[i][j] = q;
      }
    }
  }

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
      colonne.push_back(matrixpair.second);
    }
    righe.push_back(colonne.back());
    for (int i = 0; i < righe.size(); i++)
      cout << righe[i] << " ";
    cout << endl;
    cout << MatrixChainOrder(righe, n_matrici+1) << endl;
  }
}