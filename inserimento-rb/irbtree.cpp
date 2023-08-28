#include <fstream>
#include <iostream>
#include <vector>

#define TASK 100
#define RED 0
#define BLACK 1

using namespace std;

template <class T> class Node {
public:
  T value;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;
  bool colour;
  Node(T value) {
    parent = NULL;
    left = NULL;
    right = NULL;
    colour = RED;
    this->value = value;
  }
};

template <class T>

class RBtree {
public:
  Node<T> *root;

  RBtree() { root = NULL; }

  void insert(T value) {
    Node<T> *current = root;
    Node<T> *parent = NULL;
    Node<T> *node = new Node<T>(value);

    while (current) {
      parent = current;
      if (value < current->value)
        current = current->left;
      else
        current = current->right;
    }

    if (!parent)
      root = node;
    else if (value < parent->value)
      parent->left = node;
    else
      parent->right = node;

    node->parent = parent;
    fixup_rbtree(node);
  }

  void fixup_rbtree(Node<T> *node) {
    while (node->parent && node->parent->colour == RED) {
      if (node->parent == node->parent->parent->left) {
        Node<T> *uncle = node->parent->parent->right;
        if (uncle &&
            uncle->colour == RED) { // zio rosso, non ruotiamo ma ci limitiamo a
                                    // cambiare colore tra padre-zio e nonno
          node->parent->colour = BLACK;
          uncle->colour = BLACK;
          node->parent->parent->colour = RED;
          node = node->parent->parent;
        } else {                             // altrimenti rotazione
          if (node == node->parent->right) { // caso "3"
            node = node->parent;
            rotate_left(node);
          }
          node->parent->colour = BLACK;
          node->parent->parent->colour = RED;
          rotate_right(node->parent->parent);
        }
      } else {
        Node<T> *uncle = node->parent->parent->left;
        if (uncle && uncle->colour == RED) {
          node->parent->colour = BLACK;
          uncle->colour = BLACK;
          node->parent->parent->colour = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rotate_right(node);
          }
          node->parent->colour = BLACK;
          node->parent->parent->colour = RED;
          rotate_left(node->parent->parent);
        }
      }
    }
    root->colour = BLACK;
  }

  void rotate_left(Node<T> *A) {
    Node<T> *E = A->parent; // Nodo esterno alla struttura da ruotare
    Node<T> *C = A->right;
    Node<T> *c = C->left;

    C->left = A;
    A->parent = C;
    A->right = c;
    if (c != NULL)
      c->parent = A;
    C->parent = E;

    if (E == NULL)
      root = C;
    else if (E->left == A)
      E->left = C;
    else
      E->right = C;
  }

  void rotate_right(Node<T> *A) {
    Node<T> *E = A->parent; // Nodo esterno alla struttura da ruotare
    Node<T> *C = A->left;
    Node<T> *c = C->right;

    C->right = A;
    A->parent = C;
    A->left = c;
    if (c != NULL)
      c->parent = A;
    C->parent = E;

    if (E == NULL)
      root = C;
    else if (E->right == A)
      E->right = C;
    else
      E->left = C;
  }

  void inorder(ofstream &output, Node<T> *temp) {
    if (temp == NULL)
      return;
    inorder(output, temp->left);
    output << "(" << temp->value << " ";
    if (temp->colour == RED)
      output << "R"
             << ") ";
    else
      output << "B"
             << ") ";
    inorder(output, temp->right);
  }

  void preorder(ofstream &output, Node<T> *node) {
    if (node) {
      output << "(" << node->value << " " << (node->colour == BLACK ? "B" : "R")
             << ") ";
      preorder(output, node->left);
      preorder(output, node->right);
    }
  }

  void postorder(ofstream &output, Node<T> *temp) {
    if (temp == NULL)
      return;

    postorder(output, temp->left);
    postorder(output, temp->right);
    output << "(" << temp->value << " ";
    if (temp->colour == RED)
      output << "R"
             << ") ";
    else
      output << "B"
             << ") ";
  }
};
int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");

  string type;
  int node;
  string print_type;
  string value;

  for (int i = 0; i < TASK; i++) {
    input >> type >> node >> print_type;
    if (type == "double") {
      RBtree<double> tree = RBtree<double>();

      for (int j = 0; j < node; j++) {
        input >> value;
        tree.insert(stod(value));
      }

      if (print_type == "inorder") {
        tree.inorder(output, tree.root);
      } else if (print_type == "preorder") {
        tree.preorder(output, tree.root);
      } else {
        tree.postorder(output, tree.root);
      }
      output << endl;
    } else {
      RBtree<int> tree = RBtree<int>();

      for (int j = 0; j < node; j++) {
        input >> value;
        tree.insert(stoi(value));
      }

      if (print_type == "inorder") {
        tree.inorder(output, tree.root);
      } else if (print_type == "preorder") {
        tree.preorder(output, tree.root);
      } else {
        tree.postorder(output, tree.root);
      }
      output << endl;
    }
  }
}