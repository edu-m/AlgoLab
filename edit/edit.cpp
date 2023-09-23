#include <fstream>
#include <iostream>
#include <vector>

#define TASK 1

using namespace std;

int edit(int sl1, int sl2, string s1, string s2) {
  vector<vector<int>> matrix(sl1 + 1, vector<int>(sl2 + 1, 0));

  for (int i = 0; i < sl1 + 1; i++)
    matrix[i][0] = i;
  for (int j = 0; j < sl2 + 1; j++)
    matrix[0][j] = j;

  for (int i = 1; i < sl1 + 1; i++)
    for (int j = 1; j < sl2 + 1; j++)
      if (s1[i - 1] == s2[j - 1])
        matrix[i][j] = matrix[i - 1][j - 1]; // match
      else
        matrix[i][j] =
            min(matrix[i - 1][j - 1], min(matrix[i - 1][j], matrix[i][j - 1])) +
            1;
for(int i = 0;i<sl1+1;i++){
	for(int j=0;j<sl2+1;j++)
		cout << matrix[i][j] << " ";
	cout << endl;
}
  return matrix[sl1][sl2];
}
int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");

  int sl1;
  int sl2;
  string s1;
  string s2;

  for (int i = 0; i < TASK; i++) {
    input >> sl1 >> sl2 >> s1 >> s2;
    output << edit(sl1, sl2, s1, s2) << endl;
  }
}
