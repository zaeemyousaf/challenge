#ifndef _HASH_H
#define _HASH_H

#include <iostream>
template <class v>
struct HashItem{
  int key;
  v value;
  short status;
  HashItem(){
    status = 0;
  }
}; 
//-------------------
template <class v>
class HashMap{
 private:
  HashItem<v>* hashArray;
  int capacity;
  int currentElements;
  virtual int getNextCandidateIndex(int key, int i);
  void doubleCapacity();

 public:
  HashMap(); 
  HashMap(int const capacity);
  void insert(int const key, v const value);
  bool deleteKey(k const key) const;
  v* get(k const key) const;
  ~HashMap();
};
#endif
