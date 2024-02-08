#ifndef INCLUDE_SET_CC
#define INCLUDE_SET_CC

namespace MySet {

class Set {
  int value;
  short height;
  Set *left, *right;

 public:
  Set(int value);
  Set(const Set& other);
  void swaps(Set& other);
  Set& operator=(const Set& other);
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