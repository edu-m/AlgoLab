#include <fstream>
#include <iostream>
#include <vector>
#define TASK 3
using namespace std;
int heapifyCount;

int getLeft(int index) { return index * 2 + 1; }
int getRight(int index) { return index * 2 + 2; }

template <class T> void heapify(vector<T> &queue, int index) {
  // cout <<index<<endl;
  ++heapifyCount;
  int l = index * 2 + 1;
  int r = index * 2 + 2;
  int max = index;
  if (l < queue.size() && queue[l] > queue[max])
    max = l;

  if (r < queue.size() && queue[r] > queue[max])
    max = r;

  if (max != index) {
    swap(queue[max], queue[index]);
    heapify(queue, max);
  }
}

template <class T> void extractMax(vector<T> &heap) {
  swap(heap[0], heap[heap.size() - 1]);
  heap.pop_back();
  heapify(heap, 0);
}

template <class T> void buildMaxHeap(vector<T> &heap) {
  for (int i = heap.size() / 2 - 1; i >= 0; i--) // faccio il build heap
    heapify(heap, i);

  for (int i = heap.size() - 1; i > 0; i--)
    extractMax(heap);
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  string type, temp;
  int number;
  for (int i = 0; i < TASK; i++) {
    heapifyCount = 0;
    input >> type >> number;
    if (type == "int") {
      vector<int> heap = vector<int>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        heap.push_back(stoi(temp));
      }

      buildMaxHeap(heap);

    } else if (type == "double") {
      vector<double> heap = vector<double>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        heap.push_back(stod(temp));
      }

      buildMaxHeap(heap);

      ;
    } else if (type == "bool") {
      vector<bool> heap = vector<bool>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        heap.push_back(stoi(temp));
      }

      buildMaxHeap(heap);

    } else if (type == "char") {
      vector<char> heap = vector<char>();
      for (int j = 0; j < number; j++) {
        input >> temp;
        heap.push_back(temp[0]);
      }

      buildMaxHeap(heap);
    }
    output << heapifyCount << endl;
  }
}