#include "BST.h"
#include <fstream>
#include <iostream>
#include <sstream>
#define TASK 100
using namespace std;
#define IS_ROT_RIGHT temp.find("right") != string::npos

string getValue(string input) {
  if (input.find("ins:") != string::npos) // caso inserimento
    input.erase(0, 4);
  else if (input.find("left:") != string::npos)
    input.erase(0, 5);
  else if (input.find("right:") != string::npos)
    input.erase(0, 6);
  else if (input.find("canc:") != string::npos)
    input.erase(0, 5);
  return input;
}

int main() {
  // int 5 2 postorder ins:130 ins:144 ins:23 ins:240 ins:192 right:23 right:144
  ifstream input("input.txt");
  ofstream output("output.txt");
  BST<int> bst;
  string type;
  int n_ops, n_rots;
  string print_type, temp, rot_val;
  for (int i = 0; i < TASK; i++) {
    bst = BST<int>();
    input >> type >> n_ops >> n_rots >> print_type;

    if (type == "int") {

      for (int j = 0; j < n_ops; j++) {
        input >> temp;
        // cout << getValue(temp) << endl;
        bst.insert(stoi(getValue(temp)));
      }

      // cout << endl;
      for (int j = 0; j < n_rots; j++) {
        input >> temp;
        if (IS_ROT_RIGHT) {
          bst.rotate_right(stoi(getValue(temp)));
        } else
          bst.rotate_left(stoi(getValue(temp)));
      }
      if (print_type == "inorder")
        bst.inorder(output, bst.root);
      else if (print_type == "preorder")
        bst.preorder(output, bst.root);
      else
        bst.postorder(output, bst.root);
      output << endl;
    } else if (type == "double") {

      for (int j = 0; j < n_ops; j++) {
        input >> temp;
        // cout << getValue(temp) << endl;
        bst.insert(stod(getValue(temp)));
      }

      // cout << endl;
      for (int j = 0; j < n_rots; j++) {
        input >> temp;
        if (IS_ROT_RIGHT)
          bst.rotate_right(stod(getValue(temp)));
        else
          bst.rotate_left(stod(getValue(temp)));
      }
      if (print_type == "inorder")
        bst.inorder(output, bst.root);
      else if (print_type == "preorder")
        bst.preorder(output, bst.root);
      else
        bst.postorder(output, bst.root);
      output << endl;
    }
  }
}