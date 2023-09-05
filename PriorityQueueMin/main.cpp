#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#if 0
#define TASK 1
#else
#define TASK 100
#endif

int heapifycount;

string parseInput(string input) {
  if (input.find(':') == string::npos) // non troviamo ':', è una extract
    return input;
  return input.substr(2, input.length());
}


int getParent(int index) { return index / 2 - (index % 2 == 0); }
int getLeft(int index) { return index * 2 + 1; }
int getRight(int index) { return index * 2 + 2; }

template <class T> void heapify(vector<T> &queue, int index) {
  // output <<index<<endl;
  ++heapifycount;
  int l = getLeft(index);
  int r = getRight(index);
  int min = index;

  if (l < queue.size() - 1 && queue[l] < queue[min])
    min = l;
  if (r < queue.size() - 1 && queue[r] < queue[min])
    min = r;

  if (min != index) {
    // output << "swap tra " << queue[min] << " e " << queue[index] << endl;
    swap(queue[min], queue[index]);
    heapify(queue, min);
  }
}

template <class T> void insert(vector<T> &queue, T key) {
  // output << key << endl;
  queue.push_back(key);
  int index = queue.size() - 1;

  while (index > 0 && queue[getParent(index)] > queue[index]) {
    swap(queue[getParent(index)], queue[index]);
    index = getParent(index);
  }
}
template <class T> void extractMin(vector<T> &queue) {
  if (queue.size() == 0)
    return;
  if (queue.size() == 1) {
    // output << "size = 1"<<endl;
    queue.pop_back();
    return;
  }
  swap(queue[0], queue[queue.size() - 1]);
  queue.pop_back();
  // output << "chiamata heapify su " << queue.size()<<endl;
  heapify(queue, 0);
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  string type, temp;
  int number;
  for (int i = 0; i < TASK; i++) {
    heapifycount = 0;
    input >> type >> number;
    if (type == "int") {
      vector<int> queue;
      queue.resize(0);
      for (int j = 0; j < number; j++) {
        input >> temp;
        // output << temp << " ";
        string parsed = parseInput(temp);
        if (parsed == "extract") {
          extractMin(queue);
        } else {
          // output << "inserisco "<<parsed<<" ";
          insert(queue, stoi(parsed));
        }
      }
      output << heapifycount << " ";
      for (int j = 0; j < queue.size(); j++) {
        output << queue[j] << " ";
      }
      output << endl;
    }
    if (type == "char") {
      vector<char> queue;
      queue.resize(0);
      for (int j = 0; j < number; j++) {
        input >> temp;
        string parsed = parseInput(temp);
        if (parsed == "extract") {
          extractMin(queue);
        } else {
          insert(queue, parsed[0]);
        }
      }
      output << heapifycount << " ";
      for (int j = 0; j < queue.size(); j++) {
        output << queue[j] << " ";
      }
      output << endl;
    }
    if (type == "bool") {
      vector<int> queue;
      queue.resize(0);
      for (int j = 0; j < number; j++) {
        input >> temp;
        // output << temp << " ";
        string parsed = parseInput(temp);
        if (parsed == "extract") {
          extractMin(queue);
        } else {
          // output << "inserisco "<<parsed<<" ";
          insert(queue, stoi(parsed));
        }
      }
      output << heapifycount << " ";
      for (int j = 0; j < queue.size(); j++) {
        output << queue[j] << " ";
      }
      output << endl;
    }
    if (type == "double") {
      vector<double> queue;
      queue.resize(0);
      for (int j = 0; j < number; j++) {
        input >> temp;
        // output << temp << " ";
        string parsed = parseInput(temp);
        if (parsed == "extract") {
          extractMin(queue);
        } else {
          // output << "inserisco "<<parsed<<" ";
          insert(queue, stod(parsed));
        }
      }
      output << heapifycount << " ";
      for (int j = 0; j < queue.size(); j++) {
        output << queue[j] << " ";
      }
      output << endl;
    }
  }
}