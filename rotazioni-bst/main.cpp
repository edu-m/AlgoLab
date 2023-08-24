#include <fstream>
#include <iostream>
#include <sstream>
#define TASK 1
using namespace std;
#define IS_ROT_RIGHT temp.find("right") != string::npos

string getRotationValue(string input) {
  input.replace(input.find(":"), 1, " ");
  stringstream stream(input);
  string ret;
  stream >> ret >> ret;
  return ret;
}

int main() {
  // int 5 2 postorder ins:130 ins:144 ins:23 ins:240 ins:192 right:23 right:144
  ifstream input("input.txt");
  string type;
  int n_ops, n_rots;
  string print_type, temp, rot_val;
  for (int i = 0; i < TASK; i++) {
    input >> type >> n_ops >> n_rots >> print_type;
    for (int j = 0; j < n_ops; j++) {
      input >> temp;
      cout << "aggiunto " << temp.substr(4, temp.length() - 4) << endl;
    }
    for (int j = 0; j < n_rots; j++) {
      input >> temp;
      rot_val = getRotationValue(temp);
      cout << "rotazione verso ";
      if (IS_ROT_RIGHT)
        cout << "destra ";
      else
        cout << "sinistra ";
      cout << "su " << rot_val << endl;
    }
  }
}