#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#define TASK 3
using namespace std;
int matOrder(vector<int> array, int n) {
  int minMul[n][n]; // holds the number of scalar multiplication needed
  for (int i = 1; i < n; i++)
    minMul[i][i] = 0; // for multiplication with 1 matrix, cost is 0
  for (int length = 2; length < n;
       length++) { // find the chain length starting from 2
    for (int i = 1; i < n - length + 1; i++) {
      int j = i + length - 1;
      minMul[i][j] = INT_MAX; // set to infinity
      for (int k = i; k <= j - 1; k++) {
        // store cost per multiplications
        int q = minMul[i][k] + minMul[k + 1][j] +
                array[i - 1] * array[k] * array[j];
        if (q < minMul[i][j])
          minMul[i][j] = q;
      }
    }
  }
  return minMul[1][n - 1];
}
pair<int, int> getMatrixNumbers(string input) {
  input = input.substr(1, input.length() - 2);
  input.replace(input.find('x'), 1, " ");
  //   cout << input << endl;
  string m1, m2;
  stringstream istr(input);
  istr >> m1 >> m2;
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
    cout << matOrder(righe, n_matrici) << endl;
  }
}