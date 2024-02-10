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

};

class Set {
  struct Node {
    int value;
    Node *left, *right;
    short height;
  };

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

 private:
  void balanceTree();
  void smallLeftRotate();
  void smallRightRotate();
  void bigLeftRotate();
  void bigRightRotate();
};

}  // namespace MySet
#endif