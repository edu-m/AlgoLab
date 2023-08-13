#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#if 0
#define TASK 3
#else
#define TASK 100
#endif

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  int numero, peso;
  int temp;
  priority_queue<int> queue;
  for (int i = 0; i < TASK; i++) {
    queue = priority_queue<int>();
    input >> numero >> peso;
    for (int j = 0; j < numero; j++) {
      input >> temp;
      queue.push(temp);
    }
    int count = 0;
    for (int i = 0; i < peso; i++) {
      count += queue.top();
      queue.pop();
    }
    output << count << endl;
  }
}