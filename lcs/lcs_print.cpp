#include <fstream>
#include <iostream>
#include <vector>
#define TASK 100

using namespace std;

vector<char> lcs(string x, string y, int m, int n) {
  vector<vector<int>> matrix(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i < m + 1; i++)
    for (int j = 1; j < n + 1; j++)

      if (x[i - 1] == y[j - 1])
        matrix[i][j] = matrix[i - 1][j - 1] + 1;
      else
        matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);

  int index = matrix[m][n];
  vector<char> lcs(index);
  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (x[i - 1] == y[j - 1]) {
      lcs[--index] = x[i - 1];
      --i;
      --j;
    } else if (matrix[i - 1][j] > matrix[i][j - 1])
      --i;
    else
      --j;
  }
  return lcs;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int size0, size1;
  string string0, string1;
  for (int i = 0; i < TASK; i++) {
    input >> size0 >> size1 >> string0 >> string1;
    vector<char> _lcs = lcs(string0, string1, size0, size1);
    for (const auto &e : _lcs)
      output << e;
    output << endl;
  }
}
