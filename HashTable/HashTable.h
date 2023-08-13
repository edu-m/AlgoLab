#pragma once
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <vector>
#define CONST_MUL_HASH 0.61803

using namespace std;

template <class T> class HashTable {
  list<T> *table;
  int size;  // numero di nodi occupati
  int slots; // numero di posti occupabili
  int hash(T key) {
#if 0
        return int(key) % this->slots;
#else
    return int(this->slots * fmod(key * CONST_MUL_HASH, 1));
#endif
  }

public:
  int getSize() { return this->size; }
  int getSlots() { return this->slots; }
  HashTable<T>(int _slots) {
    this->slots = _slots;
    this->size = 0;
    table = new list<T>[this->slots];
  }
  HashTable<T>(int _slots, int _size, T *data) {
    this->slots = _slots;
    table = new list<T>[this->slots];
    for (int i = 0; i < _size; i++) {
      this->insertKey(data[i]);
    }
  }
  HashTable<T> *insertKey(T key) {
    table[hash(key)].push_back(key);
    ++size;
    return this;
  }
  void print() {
    for (int i = 0; i < this->slots; i++) {
      typename list<T>::iterator it;
      for (it = table[i].begin(); it != table[i].end(); it++)
        cout << *it << " ";
      cout << "\n";
    }
  }
  void print_output() {
    ofstream file;
    file.open("output.txt", std::ofstream::out | std::ofstream::app);
    for (int i = 0; i < slots; i++) {
      file << this->table[i].size() << " ";
      // if (i < slots - 1)
      //     file << " ";
    }
    file << "\n";
  }
};
