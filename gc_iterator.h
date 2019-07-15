#pragma once

#include <string>

// Exception Interface
class BaseExc { public: virtual std::string desc() = 0; };

// Exception thrown when an attempt is made to
// use an Iter that exceeds the range of the
// underlying object.
class OutOfRangeExc : public BaseExc {
  // Add functionality if needed by your application.
public:
  std::string desc() { return "Out Of Range Excption!"; }
};


// An iterator-like class for cycling through arrays
// that are pointed to by GCPtrs. Iter pointers
// ** do not ** participate in or affect garbage
// collection. Thus, an Iter pointing to
// some object does not prevent that object
// from being recycled.
template <class T>
class Iter {
  T *ptr;          // current pointer value
  T *end;          // points to element one past end
  T *begin;        // points to start of allocated array
  unsigned length; // length of sequence

  void checkrange() {
    if ((ptr >= end) || (ptr < begin))       throw OutOfRangeExc();
  }
  void checkrange(int idx) {
    if ((idx < 0) || (idx >= (end - begin))) throw OutOfRangeExc();
  }

public:
  Iter() : ptr(nullptr), begin(nullptr), end(nullptr), length(0) {}

  Iter(T *p, T *first, T *last) : ptr(p), begin(first), end(last) {
    length = end - begin;
  }

  // Return length of sequence to which this
  // Iter points.
  unsigned size()   { return length;             }

  // Return value pointed to by ptr.
  // Do not allow out-of-bounds access.
  T &operator*()    { checkrange(); return *ptr; }

  // Return address contained in ptr.
  // Do not allow out-of-bounds access.
  T *operator->()   { checkrange(); return ptr;  }

  // Prefix ++.
  Iter operator++() { ++ptr; return *this;       }

  // Prefix --.
  Iter operator--() { --ptr; return *this;       }

  // Postfix ++.
  Iter operator++(int) {
    T *tmp = ptr;
    ptr++;
    return Iter<T>(tmp, begin, end);
  }

  // Postfix --.
  Iter operator--(int) {
    T *tmp = ptr;
    ptr--;
    return Iter<T>(tmp, begin, end);
  }

  // Return a reference to the object at the
  // specified index. Do not allow out-of-bounds
  // access.
  T &operator[](int i) { checkrange(i); return ptr[i];   }

  // Define the relational operators.
  bool operator==(Iter op2)    { return ptr == op2.ptr;  }

  bool operator!=(Iter op2)    { return ptr != op2.ptr;  }

  bool operator< (Iter op2)    { return ptr <  op2.ptr;  }

  bool operator<=(Iter op2)    { return ptr <= op2.ptr;  }

  bool operator> (Iter op2)    { return ptr >  op2.ptr;  }

  bool operator>=(Iter op2)    { return ptr >= op2.ptr;  }

  // Subtract an integer from an Iter.
  Iter operator-(int n)        { ptr -= n; return *this; }

  // Add an integer to an Iter.
  Iter operator+(int n)        { ptr += n; return *this; }

  // Return number of elements between two Iters.
  int operator-(Iter<T> &itr2) { return ptr - itr2.ptr;  }
};
