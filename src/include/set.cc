#ifndef INCLUDE_SET_H
#define INCLUDE_SET_H
#include "set.h"

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
  if (this) {
    if (this->left) delete this->left;
    if (this->right) delete this->right;
  }
}

void Node::print() const {
  if (this->left) {
    std::cout << '(';
    this->left->print();
    std::cout << ')';
  }
  std::cout << this->value;
  if (this->right) {
    std::cout << '(';
    this->right->print();
    std::cout << ')';
  }
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
  else if (key > this->value) {
    if (this->right)
      isKeyInserted = this->right->insert(key, this->right);
    else {
      isKeyInserted = true;
      this->right = new Node(key);
    }
  }
  
    this->calculateHeight();
    node = this->balanceTree();
  
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
    } else if (left_bfactor == 1) {
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
  this->right = this->right->smallRightRotate();
  return this->smallLeftRotate();
}

Node* Node::bigRightRotate() {
  this->left = this->left->smallLeftRotate();
  return this->smallRightRotate();
}

int Node::getDeleteMinimum(Node*& node) {
  Node* temp;
  int min;
  if (this->left) {
    min = this->left->getDeleteMinimum(temp);
    if (temp != this->left) {
      this->left->right = nullptr;
      this->left->left = nullptr;
      delete this -> left;
      this->left = temp;
    }
  } else {
    min = this->value;
  }
  node = this->right;
  return min;
}

int Node::getDeleteMaximum(Node*& node) {
  Node* temp;
  int max;
  if (this->right) {
    max =  this->right->getDeleteMaximum(temp);
    if (temp != this->right) {
      this->right->right = nullptr;
      this->right->left = nullptr;
      delete this->right;
      this->right = temp;
    }
  } else {
    max = this->value;
  }
  node = this->left;
  return max;
}

Node* Node::deleteNode() {
  Node* temp;
  if (this->right) {
    this->value = this->right->getDeleteMinimum(temp);
    if (temp != this->right) {
      this->right->right = nullptr;
      this->right->left = nullptr;
      delete this->right;
      this->right = temp;
    } 
  } else if (this->left) {
    this->value = this->left->getDeleteMaximum(temp);
    if (temp != this->left) {
      this->left->right = nullptr;
      this->left->left = nullptr;
      delete this->left;
      this->left = temp;
    }
  }
  else {
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
  bool flag = false;
  if (key < this->value) {
    if (this->left) {
      flag = this->left->erase(key, temp);
      if (!temp) {
        this->left->right = nullptr;
        this->left->left = nullptr;
        delete this->left;
        this->left = nullptr;
      }
    }
      
    else
      return false;
  }
  if (key > this->value) {
    if (this->right) {
      flag = this->right->erase(key, temp);
      if (!temp) {
        this->right->right = nullptr;
        this->right->left = nullptr;
        delete this->right;
        this->right = nullptr;
      }
    }
    else
      return false;
  }
  return flag;
}

bool Node::contains(int key) const {
  if (this->value == key) return true;
  if (key < this->value) {
    if (this->left)
      return this->left->contains(key);
    else
      return false;
  }
  if (this->right)
    return this->right->contains(key);
  else
    return false;
}

Set::Set() { this->root = nullptr; }
Set::Set(const Set& other) { this->root = new Node(*(other.root)); }
void Set::swaps(Set& other) { std::swap(this->root, other.root); }
Set Set::operator=(const Set& other) {
  Set copy(other);
  this->swaps(copy);
  return *(this);
}
void Set::print() const {
  if (this->root)
    this->root->print();
  else
    std::cout << "The set is empty";
}

bool Set::insert(int key) {
  if (this->root)
    return this->root->insert(key, this->root);
  else {
    this->root = new Node(key);
    return true;
  }
}

Set::~Set() { if(this->root) delete this->root; }
bool Set::contains(int key) const {
  return this->root ? this->root->contains(key) : false;
}

bool Set::erase(int key) {
  bool flag = false;
  if (this->root) {
    Node* temp = this->root;
    flag = this->root->erase(key, temp);
    if (!temp) {  
      delete this->root;
      this->root = nullptr;
    } else
      this->root = temp;
  }
  return flag;
}
}  // namespace MySet
#endif