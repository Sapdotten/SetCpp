#ifndef INCLUDE_SET_H
#define INCLUDE_SET_H
#include "set.h"

#include "cmath"
#include "iostream"
namespace MySet {
Set::Set(int value) {
  this->value = value;
  this->left = nullptr;
  this->right = nullptr;
  this->height = 0;
}

Set::Set(const Set& other) {
  this->height = other.height;
  this->value = other.value;
  if (other.left != nullptr)
    this->left = new Set(*(other.left));
  else
    this->left = nullptr;
  if (other.right != nullptr)
    this->right = new Set(*(other.right));
  else
    this->right = nullptr;
}

void Set::swaps(Set& other) {
  std::swap(this->value, other.value);
  std::swap(this->left, other.left);
  std::swap(this->right, other.right);
}

Set& Set::operator=(const Set& other) {
  Set copy(other);
  this->swaps(copy);
  return *(this);
}

void Set::print() const {
  if (this->left) this->left->print();
  std::cout << this->value << " ";
  if (this->right) this->right->print();
}
bool Set::insert(int key) {
  bool is_key_inserted = false;
  if (key < this->value) {
    if (this->left)
      is_key_inserted = this->left->insert(key);
    else {
      is_key_inserted = true;
      this->left = new Set(key);
      if (this->height < 1) this->height = 1;
    }
  }
  if (key > this->value) {
    if (this->right)
      is_key_inserted = this->right->insert(key);
    else {
      is_key_inserted = true;
      this->right = new Set(key);
      if (this->height < 1) this->height = 1;
    }
  } else
    return false;
  this->height = this->left->height >= this->right->height
                     ? this->left->height
                     : this->right->height;
  if (abs(this->left->height - this->right->height) > 1) {
    this->balanceTree();
  }
  return is_key_inserted;
}

bool Set::contains(int key) const {
  if (key < this->value) {
    {
      if (this->left)
        return this->left->contains(key);
      else
        return false;
    }
  } else if (key > this->value) {
    if (this->right)
      return this->right->contains(key);
    else
      return false
  } else
    return true;
}
bool Set::erase(int key) {
  if (key < this->value) {
    {
      if (this->left)
        return this->left->contains(key);
      else
        return false;
    }
  } else if (key > this->value) {
    if (this->right)
      return this->right->contains(key);
    else
      return false
  } else {
  //здесь нужно будет рассмотреть четыре различных случая
  };
}
}  // namespace MySet
#endif