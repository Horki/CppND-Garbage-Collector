// test

#include <iostream>
#include <memory>
#include <list>
#include <iterator>
#include <algorithm>

#include "gc_pointer.h"
#include "LeakTester.h"

int main() {
  {
    Pointer<int> p = new int(19);
    std::cout << "*p = " << *p << ", addr = " << p << std::endl;
    p.showlist();
    p = new int(21);
    std::cout << "*p = " << *p << ", addr = " << p << std::endl;
    p.showlist();
    p = new int(28);
    std::cout << "*p = " << *p << ", addr = " << p << std::endl;
    p.showlist();
  }
  std::cout << "custom pointer scope done\n";

  {
    Pointer<int> p1(new int(19));
    Pointer<int> p2 = p1;
    Pointer<int> p3 = new int(10);
    int *p4 = p3;
    // p = new int(21);
    std::cout << "*p1 = " << *p1 << std::endl;
    std::cout << "*p2 = " << *p2 << std::endl;
    std::cout << "*p3 = " << *p3 << std::endl;
    std::cout << "*p4 = " << *p4 << std::endl;
    p1.showlist();
    p2.showlist();
    p3.showlist();
  }
  std::cout << "custom pointer scope done\n";

  {
    int size = 3;
    Pointer<float, 3> p2(new float[size] {1.1, 2.2, 3.3});
    Pointer<float, 3> p3(p2); // copy constructor
    for (int i = 0; i < size; ++i) std::cout << p2[i] << ", ";
    std::cout << std::endl;
    for (auto iter : p3)           std::cout << iter  << ", ";
    std::cout << std::endl;

    p2.showlist();
    p3.showlist();
  }
  std::cout << "custom pointer scope done\n";
  {
    Pointer<std::list<int>> p3(new std::list<int>{1, 2, 3});
    std::ostream_iterator<int> out(std::cout, ", ");
    std::copy(p3->begin(), p3->end(), out);
    std::cout << std::endl;
  }
  std::cout << "custom pointer scope done\n";
  {
    std::unique_ptr<std::list<float>> p3(new std::list<float>{1.1, 2.2, 3.3});
    std::ostream_iterator<float> out(std::cout, ", ");
    std::copy(p3->begin(), p3->end(), out);
    std::cout << std::endl;
  }
  std::cout << "unique pointer scope done\n";


  {
    std::shared_ptr<int> p(new int(10));
    std::cout << "*p = " << *p << std::endl;
    // p = new int(11);
    // std::cout << "*p = " << *p << std::endl;
  }
  std::cout << "shared pointer scope done\n";

}
