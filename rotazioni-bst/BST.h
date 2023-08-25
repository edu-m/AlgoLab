#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
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
  BST() : root(NULL) {}

  void insert(T value) {
    Node<T> *newNode = new Node<T>(value);
    Node<T> *current = this->root;
    Node<T> *parent = NULL;
    while (current) {
      parent = current;
      if (value < current->value)
        current = current->left;
      else
        current = current->right;
    }
    newNode->parent = parent;
    if (!parent)
      root = newNode;
    else if (value < parent->value)
      parent->left = newNode;
    else
      parent->right = newNode;
  }

  Node<T> *search(Node<T> *node, T value) {
    if (node == NULL)
      return NULL;
    else if (node->value == value)
      return node;
    else if (node->value > value)
      return search(node->left, value);
    else if (node->value < value)
      return search(node->right, value);
    return NULL;
  }

  void rotate_left(T value) {
    Node<T> *A = search(root, value);
    // cout << A->value << endl;

    if (A == NULL)
      return;

    Node<T> *C = A->right;
    if (!C)
      return;
    A->right = C->left;
    if (C->left)
      C->left->parent = A;
    // cout << "C->parent = A->parent" << endl;
    C->parent = A->parent;
    if (!A->parent)
      root = C;
    else if (A == A->parent->right)
      A->parent->right = C;
    else
      A->parent->left = C;
    // cout << "setto C->left = A" << endl;
    C->left = A;
    A->parent = C;
    // cout << "end" << endl;
  }
  void rotate_right(T value) {
    Node<T> *A = search(root, value);
    // cout << A->value << endl;

    if (A == NULL)
      return;
    Node<T> *C = A->left;
    if (!C)
      return;

    A->left = C->right;
    if (C->right)
      C->right->parent = A;
    // cout << "C->parent = A->parent" << endl;
    C->parent = A->parent;
    if (!A->parent)
      root = C;
    else if (A == A->parent->left)
      A->parent->left = C;
    else
      A->parent->right = C;
    // cout << "setto C->right = A" << endl;
    C->right = A;
    A->parent = C;
    // cout << "end" << endl;
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
