#include "noderb.h"
#include <iostream>

using namespace std;

template <class T> class RBtree {
  rbnode<T> *root;
  void rotate_right(rbnode<T> *node) {
    rbnode<T> *node_parent = node->getParent();
    rbnode<T> *fulcro = node->getLeft();
    rbnode<T> *fulcro_child_right = fulcro->getRight();
    fulcro->setRight(node);
    node->setParent(fulcro);
    node->setLeft(fulcro_child_right);
    fulcro_child_right->setParent(node);
    if (node_parent == NULL)
      this->root = fulcro;
    else
      fulcro->setParent(node_parent);
  }

  void rotate_left(rbnode<T> *node) {
    rbnode<T> *node_parent = node->getParent();
    rbnode<T> *fulcro = node->getRight();
    rbnode<T> *fulcro_child_right = fulcro->getLeft();
    fulcro->setLeft(node);
    node->setParent(fulcro);
    node->setRight(fulcro_child_right);
    fulcro_child_right->setParent(node);
    if (node_parent == NULL)
      this->root = fulcro;
    else
      fulcro->setParent(node_parent);
  }

  void fixup_rbtree(rbnode<T> *node) {
    // cout << node->getValue();

    if (node->getValue() == this->root->getValue()) {
      if (node->getColor() == RED)
        node->setColor(BLACK);
      return;
    }

    if (node->getParent()->getParent() == NULL)
      return;
    if (node->getParent() == node->getParent()->getParent()->getLeft() &&
        node->getParent()->getColor() == RED) {
      if (node->getUncle() == NULL || node->getUncle()->getColor() == BLACK) {
        if (node == node->getParent()->getRight())
          rotate_left(node->getParent());
        swap_colors(node->getParent(), node->getParent()->getParent());
        rotate_right(node->getParent()->getParent());
      }
      if (node->getUncle()->getColor() == RED) {
        cout << "zio rosso con nodo di valore " << node->getUncle()->getValue() << endl;
        node->getParent()->setColor(BLACK);
        node->getUncle()->setColor(BLACK);
        node->getParent()->getParent()->setColor(RED);
        fixup_rbtree(node->getParent()->getParent());
      }
    } else if (node->getParent() ==
                   node->getParent()->getParent()->getRight() &&
               node->getParent()->getColor() == RED) { // speculare
      if (node->getUncle() == NULL || node->getUncle()->getColor() == BLACK) {
        if (node == node->getParent()->getRight())
          rotate_right(node->getParent());
        swap_colors(node->getParent(), node->getParent()->getParent());
        rotate_left(node->getParent()->getParent());
      }
      if (node->getUncle()->getColor() == RED) {
        node->getParent()->setColor(BLACK);
        node->getUncle()->setColor(BLACK);
        node->getParent()->getParent()->setColor(RED);
        fixup_rbtree(node->getParent()->getParent());
      }
    }
  }

  void inorder(rbnode<T> *node) {
    if (node == NULL)
      return;
    this->inorder(node->getLeft());
    cout << "(" << node->getValue() << "," << node->printColor() << ") ";
    this->inorder(node->getRight());
  }

  void swap_colors(rbnode<T> *a, rbnode<T> *b) {
    if (a->getColor() == b->getColor())
      return;
    a->setColor(!a->getColor());
    b->setColor(!b->getColor());
  }

public:
  RBtree<T>(T value) { this->root = new rbnode<T>(value, NULL, BLACK); }
  RBtree<T>() { this->root = NULL; }
  rbnode<T> *getRoot() { return this->root; }

  void insert(T value) {
    if (root == NULL) {
      this->root = new rbnode<T>(value, BLACK);
      return;
    }
    rbnode<T> *temp = this->root;
    rbnode<T> *parent;
    while (temp != NULL) {
      parent = temp;
      if (value < parent->getValue())
        temp = temp->getLeft();
      else
        temp = temp->getRight();
    }
    rbnode<T> *node = new rbnode<T>(value);
    if (value < parent->getValue())
      parent->setLeft(node);
    else
      parent->setRight(node);
    node->setParent(parent);
    fixup_rbtree(node);
  }
  void insert(rbnode<T> *node) { insert(node->getValue()); }
  void inorder() { this->inorder(this->root); }
};