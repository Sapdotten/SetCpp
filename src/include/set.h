#ifndef INCLUDE_SET_CC
#define INCLUDE_SET_CC

namespace MySet {

class Set;

class Node {
  friend Set;
  int value;
  Node *left, *right;
  short height;

  Node(int value);
  Node(const Node& other);
  Node operator=(const Node& other);
  ~Node();
  void swaps(Node& other);
  void print() const;
  Node* balanceTree();
  bool insert(int key, Node*& node);
  bool erase(int key, Node*& node);
  Node* deleteNode();
  bool contains(int key) const;
  void calculateHeight();
  int bfactor();
  int getDeleteMinimum(Node*& node);
  int getDeleteMaximum(Node*& node);
  Node* smallLeftRotate();
  Node* smallRightRotate();
  Node* bigLeftRotate();
  Node* bigRightRotate();
};

class Set {
  Node* root;

 public:
  Set();
  Set(const Set& other);
  void swaps(Set& other);
  Set operator=(const Set& other);
  void print() const;
  bool insert(int key);
  bool contains(int key) const;
  bool erase(int key);
  ~Set();

  
};

}  // namespace MySet
#endif