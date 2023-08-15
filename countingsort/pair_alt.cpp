#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
#define TASK 100
using namespace std;
typedef pair<int, int> paio;

int find_min(vector<paio> &vec) {
  int min = INT_MAX;
  for (int i = 0; i < vec.size(); i++)
    if (min > vec[i].first)
      min = vec[i].first;
  return min;
}

int find_max(vector<paio> &vec) {
  int max = -1;
  for (int i = 0; i < vec.size(); i++)
    if (max < vec[i].first)
      max = vec[i].first;
  return max;
}

vector<paio> countingsort(vector<paio> &A) {
  int max = find_max(A);
  int min = find_min(A);
  int var = max - min;
  // cout << max << " " << min << " "<<var<<endl;
  vector<int> C = vector<int>(var + 1, 0);
  vector<paio> B = vector<paio>(A.size());
  for (int i = 0; i < A.size(); i++) // trovo C
    ++C[A[i].first - min];
  for (int i = 1; i < var + 1; i++) // trovo C'
  {
    C[i] += C[i - 1];
  }
  cout << "0 ";
  for (int i = 0; i < var; i++) {
    cout << C[i] << " ";
  }

  for (int i = B.size() - 1; i >= 0; i--) {
    B[C[A[i].first - min] - 1].first = A[i].first;
    B[C[A[i].first - min] - 1].second = A[i].second;
    C[A[i].first - min]--;
  }
  return B;
}

paio getPaio(vector<string> &temp) {

  temp[0] = temp[0].substr(1, temp[0].length());
  temp[1] = temp[1].substr(0, temp[1].length() - 1);
  return make_pair(stod(temp[0]) * 10, stod(temp[1]) * 10);
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int number;
  paio temp_paio;
  vector<paio> paia;
  vector<string> stringtemp;
  stringtemp.resize(2);
  for (int i = 0; i < TASK; i++) {
    paia.resize(0);
    input >> number;
    for (int j = 0; j < number; j++) {
      input >> stringtemp[0];
      input >> stringtemp[1];
      temp_paio = getPaio(stringtemp);
      paia.push_back(temp_paio);
    }
    vector<paio> sorted = countingsort(paia);
    for (int j = 0; j < number; j++)
      cout << "(" << double(sorted[j].first) / 10.0 << ","
           << double(sorted[j].second) / 10.0 << ") ";
    cout << endl;
  }
}