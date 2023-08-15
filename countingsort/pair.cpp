#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define TASK 1
typedef pair<double, double> paio;

paio getPaio(vector<string> &temp) {

  temp[0] = temp[0].substr(1, temp[0].length());
  temp[1] = temp[1].substr(0, temp[1].length() - 1);
  return make_pair(stod(temp[0]), stod(temp[1]));
}

paio find_min(vector<paio> &vec) {
  paio min = make_pair(INT_MAX, INT_MAX);
  for (int i = 0; i < vec.size(); i++)
    if (min.second > vec[i].second)
      min = vec[i];
  return min;
}

paio find_max(vector<paio> &vec) {
  paio max = make_pair(0, 0);
  for (int i = 0; i < vec.size(); i++)
    if (max.second < vec[i].second)
      max = vec[i];
  return max;
}

vector<paio> countingsort(vector<paio> &A) {
  // paio max = find_max(A);
  // paio min = find_min(A);
  map<double, int> C;
  vector<paio> B;
  B.resize(A.size());
  for (const auto &el : A)
    C[el.first] = 0;

  for (int i = 0; i < A.size(); i++) {
    C[A[i].first]++;
  }
  auto it = C.begin();
  while (++it != C.end()) {
    it--;
    int temp = it->second;
    it++;
    it->second += temp;
  }
  for (int i = A.size() - 1; i >= 0; i--) {
    B[C[A[i].first] - 1].second = A[i].second;
    B[C[A[i].first] - 1].first = A[i].first;
    C[A[i].first]--;
  }
  for (int i = 0; i < B.size(); i++)
    cout << C[B[i].first] << " ";
  return B;
}

int main() {
  ifstream input("input_pair.txt");
  ofstream output("output_pair.txt");
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
      //      cout << paia[j].first << " " << paia[j].second << endl;
    }
    vector<paio> sorted = countingsort(paia);
    for (int j = 0; j < number; j++)
      cout << "(" << sorted[j].first << "," << sorted[j].second << ") ";
    cout << endl;
  }
}