#include "max_heap.h"
// template declaration and definition
// should be at one file
#include "max_heap.cpp"
#include <iostream>
#include <fstream>
void buildStudentHeap(const char *fileName,
		      MaxHeap<int, Student> &obj);
int main(){
  MaxHeap<int, Student> stdHeap;
  buildStudentHeap("students.txt", stdHeap);
  while (!stdHeap.isEmpty())
    {
      Student s;
      stdHeap.getMax(s);
      cout <<s<<endl<<endl;
      stdHeap.deleteMax();
    }
  system("pause");
  return 0;
}

void buildStudentHeap(const char *fileName, MaxHeap<int, Student> &obj){
  ifstream fin(fileName);
  int n;
  int rollNo;
  char name[20];
  float cgpa;
  
  fin >> n;
  for(int i=0; i < n; i++){
    fin >> rollNo;
    fin >> name;
    fin >> cgpa;
    // MaxHeap<int,Student> h1;
    Student s1(rollNo,name,cgpa);

    obj.insert(rollNo,s1);
  }
}
