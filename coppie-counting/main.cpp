#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#define TASK 100

using namespace std;

vector<pair<int, int>> counting_sort(ofstream &output,
                                     vector<pair<int, int>> &A) {
  int massimo = -1;
  int minimo = 201;
  for (long unsigned i = 0; i < A.size(); i++) {
    massimo = max(massimo, A[i].first);
    minimo = min(minimo, A[i].first);
  }

  int max_min = massimo - minimo;
  vector<int> C(max_min + 1, 0);
  vector<pair<int, int>> B(A.size(), make_pair(0, 0));

  for (long unsigned i = 0; i < A.size(); i++) {
    C[A[i].first - minimo]++;
  }

  for (int i = 1; i <= max_min; i++) {
    C[i] += C[i - 1];
  }
  for (long i = A.size() - 1; i >= 0; i--) {
    B[C[A[i].first - minimo] - 1] = A[i];
    C[A[i].first - minimo]--;
  }
  for (long unsigned i = 0; i < C.size(); i++) {
    output << C[i] << " ";
  }

  return B;
}

void print_array(ofstream &output, vector<pair<int, int>> &B) {
  for (long unsigned i = 0; i < B.size(); i++) {
    output << "(" << (double)B[i].first / 10.0 << " "
           << (double)B[i].second / 10.0 << ") ";
  }

  output << endl;
}
int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int size;
  string temp1, temp2;
  vector<pair<int, int>> B;
  for (int i = 0; i < TASK; i++) {
    input >> size;
    vector<pair<int, int>> A = vector<pair<int, int>>();
    for (int j = 0; j < size; j++) {
      input >> temp1 >> temp2;

      temp1 = temp1.substr(1, temp1.length() - 1);
      temp2 = temp2.substr(0, temp2.length() - 1);
      A.push_back(make_pair((int)(stod(temp1) * 10), (int)(stod(temp2) * 10)));
    }

    B = counting_sort(output, A);
    print_array(output, B);
  }
}