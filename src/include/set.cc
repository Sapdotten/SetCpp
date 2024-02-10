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
  this->height = 1;
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

void Node::print() const {
  if (this->left) this->left->print();
  std::cout << this->value << ' ';
  if (this->right) this->right->print();
}

bool Node::insert(int key, Node*& node) {
  bool isKeyInserted = false;
  if (key < this->value) {
    if (this->left)
      isKeyInserted = this->left->insert(key, this->left);
    else {
      isKeyInserted = true;
      this->left = new Node(key);
    }
  }
  if (key > this->value) {
    if (this->right)
      isKeyInserted = this->right->insert(key, this->right);
    else {
      isKeyInserted = true;
      this->left = new Node(key);
    }
  }
  if (!isKeyInserted) {
    this->calculateHeight();
    node = this->balanceTree();
  }
  return isKeyInserted;
}

void Node::calculateHeight() {
  int left_height = this->left ? this->left->height : 0;
  int right_height = this->right ? this->right->height : 0;
  this->height =
      left_height > right_height ? left_height + 1 : right_height + 1;
}

int Node::bfactor() {
  int left_height = this->left ? this->left->height : 0;
  int right_height = this->right ? this->right->height : 0;
  return left_height - right_height;
}

Node* Node::balanceTree() {
  int bfactor = this->bfactor();
  if (bfactor == 2) {
    int left_bfactor = this->left->bfactor();
    if (left_bfactor == 1 || left_bfactor == 0) {
      return this->smallRightRotate();
    } else if (left_bfactor == -1) {
      return this->bigRightRotate();
    }
  } else if (bfactor == -2) {
    int right_bfactor = this->right->bfactor();
    if (right_bfactor == -1 || right_bfactor == 0) {
      return this->smallLeftRotate();
    } else if (right_bfactor == 1) {
      return this->bigLeftRotate();
    }
  }
  return this;
}

Node* Node::smallLeftRotate() {
  Node* temp = this->right;
  this->right = this->right->left;
  temp->left = this;
  return temp;
}
Node* Node::smallRightRotate() {
  Node* temp = this->left;
  this->left = temp->right;
  temp->right = this;
  return temp;
}

Node* Node::bigLeftRotate() {
  this->right = this->right->smallLeftRotate();
  return this->smallLeftRotate();
}

Node* Node::bigRightRotate() {
  this->left = this->left->smallLeftRotate();
  return this->smallRightRotate();
}

int Node::getDeleteMinimum(Node*& node) {
  if (this->left) return this->left->getDeleteMinimum(this->left);
  node = this->right;
  int min = this->value;
  delete this;
  return min;
}

int Node::getDeleteMaximum(Node*& node) {
  if (this->right) return this->right->getDeleteMaximum(this->right);
  node = this->left;
  int max = this->value;
  delete this;
  return max;
}

Node* Node::deleteNode() {
  if (this->right) {
    this->value = this->right->getDeleteMinimum(this->right);
  } else if (this->left)
    this->value = this->left->getDeleteMaximum(this->left);
  else {
    delete this;
    return nullptr;
  }

  return this;
}

bool Node::erase(int key, Node*& node) {
  if (this->value == key) {
    node = this->deleteNode();
    return true;
  }
  Node* temp;
  if (key < this->value) {
    if (this->left)
      return this->left->erase(key, this->left);
    else
      return false;
  }
  if (key > this->value) {
    if (this->right)
      return this->right->erase(key, this->right);
    else
      return false;
  }
}

Set::Set() { this->root = nullptr; }
Set::Set(const Set& other) { this->root = new Node(*(other.root)); }
void Set::swaps(Set& other) { std::swap(this->root, other.root); }
Set Set::operator=(const Set& other) {
  Set copy(other);
  this->swaps(copy);
  return *(this);
}
void Set::print() const { this->root->print(); }

bool Set::insert(int key) { return this->root->insert(key, this->root); }

Set::~Set() { delete this->root; }

}  // namespace MySet
#endif