#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define RED 0
#define BLACK 1
#define TASK 100
template <class T> class Node {
public:
  T key;
  bool color;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;

  Node(T key) : key(key), color(RED), parent(NULL), left(NULL), right(NULL) {}
};

template <class T> class RBtree {
public:
  Node<T> *root;

  void fixup_rbtree(Node<T> *node) {
    while (node->parent && node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        Node<T> *uncle = node->parent->parent->right;
        if (uncle &&
            uncle->color == RED) { // zio rosso, non ruotiamo ma ci limitiamo a
                                   // cambiare colore tra padre-zio e nonno
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {                             // altrimenti rotazione
          if (node == node->parent->right) { // caso "3"
            node = node->parent;
            rotateLeft(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateRight(node->parent->parent);
        }
      } else {
        Node<T> *uncle = node->parent->parent->left;
        if (uncle && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rotateRight(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateLeft(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void rotateLeft(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left)
      y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void rotateRight(Node<T> *y) {
    Node<T> *x = y->left;
    y->left = x->right;
    if (x->right)
      x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent)
      root = x;
    else if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
    x->right = y;
    y->parent = x;
  }

  void inorder(Node<T> *node, ofstream &output) {
    if (node) {

      inorder(node->left, output);
      output << "(" << node->key << " " << (node->color == BLACK ? "B" : "R")
             << ") ";
      inorder(node->right, output);
    }
  }

  void preorder(Node<T> *node, ofstream &output) {
    if (node) {
      output << "(" << node->key << " " << (node->color == BLACK ? "B" : "R")
             << ") ";
      preorder(node->left, output);
      preorder(node->right, output);
    }
  }

  void postorder(Node<T> *node, ofstream &output) {
    if (node) {
      postorder(node->left, output);
      postorder(node->right, output);
      output << "(" << node->key << " " << (node->color == BLACK ? "B" : "R")
             << ") ";
    }
  }
  RBtree() : root(NULL) {}

  void insert(T key) {
    Node<T> *newNode = new Node<T>(key);
    Node<T> *current = root;
    Node<T> *parent = NULL;

    while (current) {
      parent = current;
      if (key < current->key)
        current = current->left;
      else
        current = current->right;
    }

    newNode->parent = parent;

    if (!parent)
      root = newNode;
    else if (key < parent->key)
      parent->left = newNode;
    else
      parent->right = newNode;

    fixup_rbtree(newNode);
  }

  void traverse(string order, ofstream &output) {

    if (order == "inorder")
      inorder(root, output);
    else if (order == "preorder")
      preorder(root, output);
    else if (order == "postorder")
      postorder(root, output);
  }

  int findHeight(Node<T> *temp) {
    if (temp == NULL)
      return 0;
    int depth_left = findHeight(temp->left);
    int depth_right = findHeight(temp->right);

    if (depth_left > depth_right)
      return ++depth_left;
    return ++depth_right;
  }
};

int main() {
  ifstream inputFile("input.txt");
  ofstream outputFile("output.txt");

  for (int i = 0; i < TASK; i++) {
    string type;
    int N;
    inputFile >> type >> N;
    if (type == "int") {
      RBtree<int> tree;
      for (int i = 0; i < N; ++i) {
        int value;
        inputFile >> value;
        tree.insert(value);
      }
      outputFile << tree.findHeight(tree.root) << endl;
    }
    if (type == "double") {
      RBtree<double> tree;
      for (int i = 0; i < N; ++i) {
        double value;
        inputFile >> value;
        tree.insert(value);
      }
      outputFile << tree.findHeight(tree.root) << endl;
    }
  }
}
