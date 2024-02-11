#include "include\set.h"
#include "iostream"
using namespace MySet;

int main() {
  Set set;
  set.print();
  set.insert(0);
  set.erase(0);
  std::cout << std::endl;
  set.print();
  std::cout << std::endl;
  for (int i = 0; i < 20; ++i) {
    set.insert(i);
  }
  set.print();
  
  for (int i = 0; i < 20; i += 2) {
    set.erase(i);
  }
  std::cout << '\n' << set.insert(2) << '\n';
  set.print();

  return 0; }


