#include "max_heap.h"
#include <iostream>
using namespace std;

template<typename k, typename v>
MaxHeap<k,v>::MaxHeap(){
  // default constructor
  arr = new HeapItem<k,v>[1];
  capacity = 1;
  totalItems =0;
  //cout << "defalut constructor\n";
}

template<typename k, typename v>
MaxHeap<k,v>::MaxHeap(int _capacity){
  arr = new HeapItem<k,v>[_capacity];
  capacity = _capacity;
  totalItems =0;
  //cout << "parametrized called\n";
}

template<typename k, typename v>
void MaxHeap<k,v>::insert(k _key, v _value){
  if(totalItems < capacity){
    // there is space
    arr[totalItems].key = _key;
    arr[totalItems].value = _value;
    totalItems++;
  }
  else{
    // grow double and insert
    grow_double();
    arr[totalItems].key = _key;
    arr[totalItems].value = _value;
    totalItems++;
  }
  //cout << "index: " << totalItems << endl;
  adjust(totalItems,(totalItems)/2);
}

template<typename k, typename v>
void MaxHeap<k,v>::grow_double(){
  int new_capacity = capacity*2;
  HeapItem<k,v> *new_arr = new HeapItem<k,v>[new_capacity];
  for(int i=0; i< capacity; i++){
    // copy old array into new_array
    new_arr[i] = arr[i];
  }
  if(arr != NULL) delete []arr;
  arr = new_arr;
  capacity = new_capacity;  
}
template<typename k, typename v>
void MaxHeap<k,v>::adjust(int cindex,int pindex){
  if(pindex !=0 && arr[cindex-1].key > arr[pindex-1].key){    
    //cout << "adjusting ...\n";
    // HeapItem<k,v> parent = arr[pindex];
    // HeapItem<k,v> child = arr[pindex];

    HeapItem<k,v> temp = arr[pindex-1];
    arr[pindex-1] = arr[cindex-1];
    arr[cindex-1] = temp;
    
    cindex = pindex;
    pindex = pindex/2;
    adjust(cindex,pindex);
  }
  return;
  }


template<typename k, typename v>
void MaxHeap<k,v>::getMax(v &_value){
  _value = arr[0].value;
}
template<typename k, typename v>
void MaxHeap<k,v>::deleteMax(){  
  arr[0] = arr[totalItems-1];
  totalItems = totalItems-1;
  // now hepify
  for(int i=0; 2*i+2 < totalItems; i++){
    int gc = arr[2*i+1].key > arr[2*i+2].key ? 2*i+1 : 2*i+2;
    if(arr[i].key < arr[gc].key){
      // if parent < greatest children then swap
      HeapItem<k,v> temp = arr[i];
      arr[i] = arr[gc];
      arr[gc] = temp;
    }
  }
} 
template<typename k, typename v>
bool MaxHeap<k,v>::isEmpty()const{
  if(totalItems >0) return false;
  return true;
}

template<typename k, typename v>
void MaxHeap<k,v>::print(){
  for(int i=0; i < totalItems; i++){
    cout << arr[i].key << ": " << arr[i].value << "\n";
  }
}
template<typename k, typename v>
MaxHeap<k,v>::~MaxHeap(){
  delete []arr;
  //cout << "heap destroyed...\n";
}

Student::Student(){
  rollNo = 0;
  cgpa = 0;
}
Student::Student(int _rollno, char* _name, float _cgpa){
  rollNo = _rollno;
  copy(name,_name);
  cgpa = _cgpa;
}

Student::Student(Student &obj){
  //cout << "student(Student) called\n";
  rollNo = obj.rollNo;
  copy(name,obj.name);
  cgpa = obj.cgpa;
}

void Student::set_roll_no(int _rollNo){ rollNo = _rollNo;}
void Student::set_name(char* _name) {copy(name,_name);}
void Student::set_cgpa(float _cgpa){cgpa = _cgpa;}
  
int Student::get_roll_no(){return rollNo;}
char* Student::get_name(){return name;}
float Student::get_cgpa(){ return cgpa;}

ostream& operator << (ostream &out, Student &obj){
  out << "student Name: " << obj.name << endl;
  out << "Roll No: " << obj.rollNo << endl;
  out << "cgpa: " << obj.cgpa << endl;
  out << "------------------------------\n";
  return out;
}

Student::~Student(){
  
}
