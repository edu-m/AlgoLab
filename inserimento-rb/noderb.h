#pragma once
#include <cstddef>
#include <iostream>
#define RED 0
#define BLACK 1
using namespace std;

template <class T> class rbnode {
public:
  T value;
  rbnode<T> *parent;
  rbnode<T> *left;
  rbnode<T> *right;
  bool color; // 0 per rosso, 1 per nero

  rbnode(T _value, rbnode<T> *_parent, bool _color) {
  this->value = _value;
  this->parent = _parent;
  this->color = _color;
  this->left = NULL;
  this->right = NULL;
}
rbnode(T _value) : rbnode<T>(_value, NULL, RED) {}
rbnode(T _value, bool _color) : rbnode<T>(_value, NULL, _color) {}
// get e set
void setValue(T _value) { this->value = _value; }
void setParent(rbnode<T> *_parent) { this->parent = _parent; }
void setLeft(rbnode<T> *_left) { this->left = _left; }
void setRight(rbnode<T> *_right) { this->right = _right; }
void setColor(bool _color) { this->color = _color; }
T getValue() { return this->value; }
rbnode<T> *getParent() { return this->parent; }
rbnode<T> *getLeft() { return this->left; }
rbnode<T> *getRight() { return this->right; }
rbnode<T> *getUncle() {
  if (this->parent == NULL || this->parent->getParent() == NULL)
    return NULL;
  rbnode<T> *grandpa = this->parent->getParent();
  if (this->parent->getParent() == NULL)
    return NULL;
  if (grandpa->getLeft() == this->parent)
    return grandpa->getRight();
  else
    return grandpa->getLeft();
}
bool getColor() { return this->color; }
char printColor() {
  if (getColor() == BLACK)
    return 'B';
  return 'R';
}
};