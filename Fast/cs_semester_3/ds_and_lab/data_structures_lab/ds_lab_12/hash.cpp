#include "hash.h"

template <class v>
HashMap<v>::HashMap(){
  hashArray = new HashItem<v>[10];
  capacity = 10;
  currentElements = 0;  
}

template <class v>
HashMap<v>::HashMap(int const _capacity){
  assert(_capacity > 1){
  hashArray = new HashItem<v>[capacity];
  capacity = _capacity;
  currentElements = 0;
  }
}

template <class v>
int HashMap<v>::getNextCandidateIndex(int key, int i){
  int hashIndex = key % capacity;
  hashIndex+=i;
  return hashIndex;
}

template <class v>
void HashMap<v>::doubleCapacity(){
  HashItem<v> *new_array = HashItem<v>[2*capacity];
  for(int i=0; i< capacity; i++){
    new_array[i].key = hashArray[i].key;
    new_array[i].value = hashArray[i].value;
    new_array[i].status = hashArray[i].status;
  }

  capacity = 2*capacity;
}

template <class v>
void HashMap<v>::insert(int const key, v const value){
  int i=1;
  int hashIndex = getNextCandidateIndex(key,i);
  while(hashArray[hashIndex].status !=0){
     hashIndex = getNextCandidateIndex(key,++i);
  }
}
