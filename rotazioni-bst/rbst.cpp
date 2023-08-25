#include <fstream>
#include <iostream>
#include <sstream>


#define TASK 1

using namespace std;

template <class T> class Node {
public:
  T value;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;

  Node(T value) {
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->value = value;
  }
};

template <class T> class BST {
public:
  Node<T> *root;

  void insert(T value) {
    if (root == NULL) {
      root = new Node<T>(value);
      return;
    }

    Node<T> *temp = root;
    Node<T> *p;
    while (temp != NULL) {
      p = temp;
      if (value < temp->value)
        temp = temp->left;
      else
        temp = temp->right;
    }
    Node<T> *inserted = new Node<T>(value);
    if (inserted->value < p->value)
      p->left = inserted;
    else
      p->right = inserted;
    inserted->parent = p;

    inorder(root);
    // cout<<"Ins"<<endl;
  }

  Node<T> *search(T value) {
    if (root == NULL)
      return NULL;

    Node<T> *temp = root;

    while (temp->left != NULL || temp->right != NULL) {
      if (value != temp->value) {
        if (value < temp->value)
          temp = temp->left;
        else
          temp = temp->right;
      } else
        return temp;
    }
    return NULL;
  }

  void rotate_left(T value) {
    Node<T> *A = search(value);

    if (A == NULL)
      return;

    if (root->right == NULL)
      return;

    Node<T> *C = A->right;
    Node<T> *c = C->left;

    if (A == root)
      root = C;
    else if (A == A->parent->left)
      A->parent->left = C;
    else
      A->parent->right = C;

    C->left = A;
    A->parent = C;
    A->right = c;
    c->parent = A;
  }

  void rotate_right(T value) {
    Node<T> *A = search(value);

    if (A == NULL)
      return;

    if (root->left == NULL)
      return;

    Node<T> *C = A->left;
    Node<T> *c = C->right;

    if (A == root)
      root = C;
    else if (A == A->parent->left)
      A->parent->left = C;
    else
      A->parent->right = C;

    C->right = A;
    A->parent = C;
    A->left = c;
    c->parent = A;
  }

  void inorder(Node<T> *temp) {
    if (temp == NULL)
      return;
    inorder(temp->left);
    cout << temp->value << " ";
    inorder(temp->right);
  }

  void inorder(ostream &output, Node<T> *temp) {
    if (temp == NULL)
      return;
    inorder(output, temp->left);
    output << temp->value << " ";
    inorder(output, temp->right);
  }
  void preorder(ostream &output, Node<T> *temp) {
    if (temp == NULL)
      return;
    output << temp->value << " ";
    preorder(output, temp->left);
    preorder(output, temp->right);
  }
  void postorder(ostream &output, Node<T> *temp) {
    if (temp == NULL)
      return;
    postorder(output, temp->left);
    postorder(output, temp->right);
    output << temp->value << " ";
  }
};

pair<string, string> trim(string temp) {
  temp.replace(temp.find(":"), 1, " ");
  stringstream ss(temp);
  pair<string, string> p;
  ss >> p.first >> p.second;

  return p;
}
int main() {

  ifstream input("input.txt");
  ofstream output("output.txt");

  string type;
  int n_operations;
  int n_rotations;
  string temp;
  string value;
  string print_type;

  for (int i = 0; i < TASK; i++) {
    input >> type >> n_operations >> n_rotations >> print_type;

    if (type == "int") {
      BST<int> tree = BST<int>();

      for (int j = 0; j < n_operations + n_rotations; j++) {
        input >> temp;
        auto op_val = trim(temp);
        // cout<<"Ciao "<<endl;
        if (op_val.first == "ins")
          tree.insert(stoi(op_val.second));
        else if (op_val.first == "left")
          tree.rotate_left(stoi(op_val.second));
        else
          tree.rotate_right(stoi(op_val.second));

        if (print_type == "inorder")
          tree.inorder(output, tree.root);
        else if (print_type == "preorder")
          tree.preorder(output, tree.root);
        else
          tree.postorder(output, tree.root);
      }
    } else {
      BST<double> tree;

      for (int j = 0; j < n_operations + n_rotations; j++) {
        input >> temp;
        auto op_val = trim(temp);
        if (op_val.first == "ins")
          tree.insert(stod(op_val.second));
        else if (op_val.first == "left")
          tree.rotate_left(stod(op_val.second));
        else
          tree.rotate_right(stod(op_val.second));

        if (print_type == "inorder")
          tree.inorder(output, tree.root);
        else if (print_type == "preorder")
          tree.preorder(output, tree.root);
        else
          tree.postorder(output, tree.root);
      }
    }
    output << endl;
  }
}