#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#define TASK 100

using namespace std;

int heapify_count;
template <class T> bool compare(tuple<T, T, T> &x, tuple<T, T, T> &y) {
  if (get<0>(x) < get<0>(y))
    return true;
  if (get<0>(x) == get<0>(y) && get<1>(x) < get<1>(y))
    return true;
  if (get<0>(x) == get<0>(y) && get<1>(x) == get<1>(y) && get<2>(x) < get<2>(y))
    return true;

  return false;
}

int getLeft(int index) { return index * 2 + 1; }
int getRight(int index) { return index * 2 + 2; }
int getParent(int index) { return index / 2 - (index % 2 == 0); }

template <class T>
void heapify(vector<tuple<T, T, T>> &a, int index, int heapsize) {
  ++heapify_count;
  int max = index;
  int l = getLeft(index);
  int r = getRight(index);

  if (l < heapsize && compare(a[max], a[l]))
    max = l;
  if (r < heapsize && compare(a[max], a[r]))
    max = r;
  if (max != index) {
    swap(a[max], a[index]);
    heapify(a, max, heapsize);
  }
}

template <class T> vector<tuple<T, T, T>> heap_sort(vector<tuple<T, T, T>> &a) {

  for (int i = (a.size() / 2) - 1; i >= 0; i--) // build heap
    heapify(a, i, a.size());
  for (int i = a.size() - 1; i > 0; i--) {
    swap(a[0], a[i]);
    heapify(a, 0, i);
  }

  return a;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");

  string type;
  int length;
  string temp1, temp2, temp3;

  for (int i = 0; i < TASK; i++) {
    heapify_count = 0;
    input >> type >> length;
    if (type == "int") {

      vector<tuple<int, int, int>> a;
      for (int j = 0; j < length; j++) {
        input >> temp1 >> temp2 >> temp3;
        a.push_back(make_tuple(stoi(temp1.substr(1, temp1.size() - 1)),
                               stoi(temp2),
                               stoi(temp3.substr(0, temp3.size() - 1))));
      }
      a = heap_sort(a);
      output << heapify_count << " ";
      for (int j = 0; j < a.size(); j++) {
        output << "(" << get<0>(a[j]) << " " << get<1>(a[j]) << " "
               << get<2>(a[j]) << ") ";
      }
      output << endl;
    }
    if (type == "double") {

      vector<tuple<double, double, double>> a;
      for (int j = 0; j < length; j++) {
        input >> temp1 >> temp2 >> temp3;
        a.push_back(make_tuple(stod(temp1.substr(1, temp1.size() - 1)),
                               stod(temp2),
                               stod(temp3.substr(0, temp3.size() - 1))));
      }
      a = heap_sort(a);
      output << heapify_count << " ";
      for (int j = 0; j < a.size(); j++) {
        output << "(" << get<0>(a[j]) <<  " " << get<1>(a[j]) <<  " "
               << get<2>(a[j]) << ") ";
      }
      output << endl;
    }
    if (type == "bool") {

      vector<tuple<bool, bool, bool>> a;
      for (int j = 0; j < length; j++) {
        input >> temp1 >> temp2 >> temp3;
        a.push_back(make_tuple(stoi(temp1.substr(1, temp1.size() - 1)),
                               stoi(temp2),
                               stoi(temp3.substr(0, temp3.size() - 1))));
      }
      a = heap_sort(a);
      output << heapify_count << " ";
      for (int j = 0; j < a.size(); j++) {
        output << "(" << get<0>(a[j]) <<  " " << get<1>(a[j]) <<  " "
               << get<2>(a[j]) << ") ";
      }
      output << endl;
    }
    if (type == "char") {

      vector<tuple<char, char, char>> a;
      for (int j = 0; j < length; j++) {
        input >> temp1 >> temp2 >> temp3;
        a.push_back(make_tuple(temp1[1], temp2[0], temp3[0]));
      }
      a = heap_sort(a);
      output << heapify_count << " ";
      for (int j = 0; j < a.size(); j++) {
        output << "(" << get<0>(a[j]) <<  " " << get<1>(a[j]) <<  " "
               << get<2>(a[j]) << ") ";
      }
      output << endl;
    }
  }
}