#ifndef INCLUDE_SET_H
#define INCLUDE_SET_H
#include "set.h"

#include "cmath"
#include "iostream"
namespace MySet {
Node::Node(int value) {
  this->left = nullptr;
  this->right = nullptr;
  this->value = value;
}
Node::Node(const Node& other) {
  this->value = other.value;
  this->height = other.height;
  if (other.left)
    this->left = new Node(*(other.left));
  else
    this->left = nullptr;
  if (other.right)
    this->right = new Node(*(other.right));
  else
    this->right = nullptr;
}

void Node::swaps(Node& other) {
  std::swap(this->value, other.value);
  std::swap(this->height, other.height);
  std::swap(this->right, this->left);
}

Node Node::operator=(const Node& other) {
  Node copy(other);
  this->swaps(copy);
  return *(this);
}

Node::~Node() {
  if (this->left) delete this->left;
  if (this->right) delete this->right;
}

Set::Set() { this->root = nullptr; }
Set::Set(const Set& other) { this->root = new Node(*(other.root)); }
}  // namespace MySet
#endif