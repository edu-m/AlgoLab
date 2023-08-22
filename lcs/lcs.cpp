#include <fstream>
#include <iostream>
#include <vector>
#define TASK 1

using namespace std;

int lcs(string x, string y, int m, int n) {
  vector<vector<int>> matrix(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i < m + 1; i++)
    for (int j = 1; j < n + 1; j++)
      if (x[i - 1] == y[j - 1])
        matrix[i][j] = matrix[i - 1][j - 1] + 1;
      else
        matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
  for (int i = 0; i < m + 1; i++) {
    for (int j = 0; j < n + 1; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
  return matrix[m][n];
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int size0, size1;
  string string0, string1;
  for (int i = 0; i < TASK; i++) {
    input >> size0 >> size1 >> string0 >> string1;
    output << lcs(string0, string1, size0, size1) << endl;
  }
}