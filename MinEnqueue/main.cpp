#include <fstream>
#include <iostream>
#include <vector>
#define TASK 100
using namespace std;

int getParent(int index) { return (index / 2 - (index % 2 == 0)); }
int getLeft(int index) { return index * 2 + 1; }
int getRight(int index) { return index * 2 + 2; }

template <class T> void heapify(vector<T> &queue, int index) {
  int min = index;
  int l = getLeft(index);
  int r = getRight(index);

  if (l < queue.size() && queue[l] < queue[min])
    min = l;
  if (r < queue.size() && queue[r] < queue[min])
    min = r;
  if (min != index) {
    swap(queue[min], queue[index]);
    heapify(queue, min);
  }
}

template <class T> void insert(vector<T> &queue, T value) {
  int index = queue.size();
  queue.push_back(value);
  while (index > 0 && queue[getParent(index)] > queue[index]) {
    swap(queue[getParent(index)], queue[index]);
    index = getParent(index);
  }
}

template <class T> void print_heap(vector<T> &queue, ofstream &output) {
  for (auto el : queue)
    output << el << " ";
  output << endl;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  string type, temp;
  int number;
  for (int i = 0; i < TASK; i++) {
    input >> type >> number;
    if (type == "int") {
      vector<int> queue = vector<int>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        insert(queue, stoi(temp));
      }
      print_heap(queue, output);
    } else if (type == "bool") {
      vector<bool> queue = vector<bool>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        insert(queue, !!stoi(temp));
      }
      print_heap(queue, output);
    } else if (type == "double") {
      vector<double> queue = vector<double>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        insert(queue, stod(temp));
      }
      print_heap(queue, output);
    } else {
      vector<char> queue = vector<char>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        insert(queue, temp[0]);
      }
      print_heap(queue, output);
    }
  }
}
