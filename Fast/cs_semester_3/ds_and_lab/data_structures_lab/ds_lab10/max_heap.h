#ifndef _MAX_HEAP_H
#define _MAX_HEAP_H

#include <iostream>
using namespace std;
template<typename Type1, typename Type2>
void copy(Type1 *&var1, Type2 *&var2){
  // copy var2 into var1
  if(var2 == 0) {
  var1=0;
  }
  else{
  int length=0;
  while(var2[length++]);
  var1 = new char[length];
  for(int i=0; i<=length; i++) var1[i]=var2[i];
  }

}

template<typename k, typename v>
struct HeapItem{
  k key;
  v value;
};

template<typename k, typename v>
class MaxHeap{
 private:
  HeapItem<k,v> *arr;
  int capacity;
  int totalItems;
public:
  MaxHeap();
  MaxHeap(int _capacity);
  void insert(k key, v value);
  void grow_double();
  void adjust(int cindex,int pindex);
  // child index, parent index
  void getMax(v &_value);
  void deleteMax();
  bool isEmpty() const;
  void print();
  ~MaxHeap();
};

class Student{
private:
  int rollNo;
  char *name;
  float cgpa;
public:
  Student();
  Student(int _rollno, char* _name, float cgpa);
  Student(Student &obj);
  void set_roll_no(int _rollNo);
  void set_name(char *_name);
  void set_cgpa(float _cgpa);
  
  int get_roll_no();
  char* get_name();
  float get_cgpa();
  friend ostream &operator << (ostream &out, Student &obj);
  ~Student();
};

#endif
