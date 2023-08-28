#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#define TASK 100
using namespace std;
int heapifyCount;

int getParent(int index) { return (index / 2 - (index % 2 == 0)); }
int getLeft(int index) { return index * 2 + 1; }
int getRight(int index) { return index * 2 + 2; }

template <class T> bool compare(pair<T, T> &a, pair<T, T> &b) {
  return (a.first > b.first || (a.first == b.first && a.second > b.second));
}

template <class T> void heapify(vector<T> &_queue, int i, int heapsize) {
  ++heapifyCount;
  int min = i;
  int l = getLeft(i); // offset di 1 per considerare la posizione 0 valida
  int r = getRight(i);

  if (l < heapsize && compare(_queue[l], _queue[min]))
    min = l;

  if (r < heapsize && compare(_queue[r], _queue[min]))
    min = r;

  if (min != i) {
    swap(_queue[i], _queue[min]);
    heapify(_queue, min, heapsize);
  }
}

template <class T> void heapsort(vector<pair<T, T>> &heap) {

  for (int i = heap.size() / 2 - 1; i >= 0; i--) // faccio il build heap
    heapify(heap, i, heap.size());

  for (int i = heap.size() - 1; i > 0; i--) {
    swap(heap[0], heap[i]);
    heapify(heap, 0, i);
  }
}

template <class T> void insert(pair<T, T> value, vector<pair<T, T>> &heap) {
  // int index = heap.size();

  // while (index > 0 && heap[getParent(index)] < heap[index]) {
  //   swap(heap[getParent(index)], heap[index]);
  //   index = getParent(index);
  // }
}

pair<string, string> parseInput(string temp, string temp1) {
  temp = temp.substr(1, temp.length() - 1);
  temp1 = temp1.substr(0, temp1.length() - 1);

  return make_pair(temp, temp1);
}

template <class T> void print_heap(vector<pair<T, T>> &heap, ofstream &output) {
  output << heapifyCount << " ";
  for (auto el : heap) {
    output << "(" << el.first << " " << el.second << ") ";
  }
  output << endl;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  string type, temp, temp1;
  int number;
  for (int i = 0; i < TASK; i++) {
    heapifyCount = 0;
    input >> type >> number;

    if (type == "int") {
      vector<pair<int, int>> heap = vector<pair<int, int>>();
      for (int j = 0; j < number; j++) {
        input >> temp >> temp1;
        pair<string, string> p1 = parseInput(temp, temp1);
        pair<int, int> pair = make_pair(stoi(p1.first), stoi(p1.second));
        heap.push_back(pair);
      }
      heapsort(heap);
      print_heap(heap, output);
    } else if (type == "bool") {
      vector<pair<bool, bool>> heap = vector<pair<bool, bool>>();
      for (int j = 0; j < number; j++) {
        input >> temp >> temp1;
        pair<string, string> p1 = parseInput(temp, temp1);
        pair<bool, bool> pair = make_pair(stoi(p1.first), stoi(p1.second));
        heap.push_back(pair);
      }
      heapsort(heap);
      print_heap(heap, output);
    } else if (type == "double") {
      vector<pair<double, double>> heap = vector<pair<double, double>>();
      for (int j = 0; j < number; j++) {
        input >> temp >> temp1;
        pair<string, string> p1 = parseInput(temp, temp1);
        pair<double, double> pair = make_pair(stod(p1.first), stod(p1.second));

        heap.push_back(pair);
      }
      heapsort(heap);
      print_heap(heap, output);
    } else {
      vector<pair<char, char>> heap = vector<pair<char, char>>();
      for (int j = 0; j < number; j++) {
        input >> temp >> temp1;
        pair<string, string> p1 = parseInput(temp, temp1);
        pair<char, char> pair = make_pair(p1.first[0], p1.second[0]);

        heap.push_back(pair);
      }
      heapsort(heap);
      print_heap(heap, output);
    }
  }
}