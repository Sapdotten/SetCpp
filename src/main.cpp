#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <chrono>
#include <ctime>
#include <iostream>
#include <random>

#include "include\set.h"
#define time \
  duration_cast<microseconds>(system_clock::now().time_since_epoch()).count()

using namespace MySet;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
int getRandomValue(int limit) { return rand() % limit; }

double getMeanCreateTime(int limit, double& insert_time, double& search_time,
                         double& delete_time) {
  srand(0);
  size_t mean_time = 0;
  for (int i = 0; i < 100; ++i) {
    cout << i << " ";

    size_t time_create_1 = time;
    Set set;
    for (int j = 0; j < limit; ++j) {
      set.insert(getRandomValue(limit * 3));
    }

    size_t time_create_2 = time;
    int value = getRandomValue(limit * 2);
    // if (i < 47) continue;
    size_t time_insert_1 = time;
    set.insert(value);
    size_t time_insert_2 = time;
    size_t time_search_1 = time;
    set.contains(value);
    size_t time_search_2 = time;
    size_t time_delete_1 = time;
    set.erase(value);
    size_t time_delete_2 = time;
    mean_time += (time_create_2 - time_create_1);
    insert_time += (time_insert_2 - time_insert_1);
    search_time += (time_search_2 - time_search_1);
    delete_time += (time_delete_2 - time_delete_1);
  }
  insert_time /= double(100.0);
  search_time /= double(100.0);
  delete_time /= double(100.0);
  return (double(mean_time) / 100);
}

void test() {
  Set set;
  set.print();
  set.insert(0);
  set.erase(0);
  cout << endl;
  set.print();
  cout << endl;
  for (int i = 0; i < 20; ++i) {
    set.insert(i);
  }
  set.print();

  for (int i = 0; i < 20; i += 2) {
    set.erase(i);
  }
  cout << '\n' << set.insert(2) << '\n';
  set.print();
}

int main() {
  double insert_time = 0, search_time = 0, delete_time = 0;
  cout << getMeanCreateTime(100000, insert_time, search_time, delete_time);
  cout << "\n"
       << "insert_time: " << insert_time << endl
       << "search_time: " << search_time << endl
       << "delete_time: " << delete_time << endl;
  /*Set set;
  for (int i = 0; i < 100; ++i) {
    set.insert(i);
  }
  for (int i = 0; i < 100; ++i) {
    Set copy(set);
    copy.erase(i);
  }
  set.print();
  set.erase(3);*/
  _CrtDumpMemoryLeaks();
  return 0;
}
