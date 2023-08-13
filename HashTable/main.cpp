#include "HashTable.h"
#include <fstream>
#include <iostream>
using namespace std;

void loadFile(string file) {
  system(": > output.txt");
  ifstream ifs(file, ifstream::in);
  while (ifs.good()) {
    string line;
    string type;
    string slots;
    string size;
    getline(ifs, type, ' ');
    getline(ifs, slots, ' ');
    getline(ifs, size, ' ');

    if (type == "int") {
      int data[stoi(size)];
      string temp;
      for (int i = 0; i < stoi(size); i++) {
        if (i == stoi(size) - 1)
          getline(ifs, temp, '\n');
        else
          getline(ifs, temp, ' ');
        data[i] = stoi(temp);
      }
      HashTable<int> hash(stoi(slots), stoi(size), data);
      hash.print_output();
    }
    if (type == "double") {
      double data[stoi(size)];
      string temp;
      for (int i = 0; i < stoi(size); i++) {
        if (i == stoi(size) - 1)
          getline(ifs, temp, '\n');
        else
          getline(ifs, temp, ' ');
        data[i] = stod(temp);
      }
      HashTable<double> hash(stoi(slots), stoi(size), data);
      hash.print_output();
    }
    if (type == "bool") {
      bool data[stoi(size)];
      string temp;
      for (int i = 0; i < stoi(size); i++) {
        if (i == stoi(size) - 1)
          getline(ifs, temp, '\n');
        else
          getline(ifs, temp, ' ');
        data[i] = stoi(temp);
      }
      HashTable<bool> hash(stoi(slots), stoi(size), data);
      hash.print_output();
    }
    if (type == "char") {
      char data[stoi(size)];
      string temp;
      for (int i = 0; i < stoi(size); i++) {
        if (i == stoi(size) - 1)
          getline(ifs, temp, '\n');
        else
          getline(ifs, temp, ' ');
        data[i] = temp[0];
      }
      HashTable<char> hash(stoi(slots), stoi(size), data);
      hash.print_output();
    }
  }
}

int main() { loadFile("input.txt"); }