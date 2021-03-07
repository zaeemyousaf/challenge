#include <iostream>
#include "student_avl.h"
#include <fstream>
using namespace std;
void popuateStudentTree(const char* fileName, AVL& avl_tree);
int main(){
  AVL stdTree;
  char name1[] = "Zaeem Yousaf";
  char name2[] = "askar hussain";
  char name3[] = "shehmeer";
  stdTree.insertStudent(2,name1,2.5);
  stdTree.insertStudent(1,name2,2.5);
  stdTree.insertStudent(4,name3,2.5);
  stdTree.insertStudent(3,name3,2.5);
  stdTree.insertStudent(0,name3,2.5);
  stdTree.insertStudent(8,name3,2.5);
  stdTree.insertStudent(20,name3,2.5);
  
  stdTree.inorderPrintStudentRollNumbers();
  cout << *stdTree.search(1);  

popuateStudentTree("students.txt", stdTree);
  //    return 0;
// cout << endl << endl << "Tree Before Deletion: " << endl;
// stdTree.inorderPrintStudentRollNumbers();
// //delete any student
// cout << endl << endl << "Tree after Deletion: " << endl;
// stdTree.inorderPrintStudentRollNumbers();
// cout<<"Data of student, whose roll number is 254, is as follows: "<< endl;
// cout << *stdTree.search(254);
}

void popuateStudentTree(const char* fileName, AVL& avl_tree){
  ifstream fin(fileName);
  int rollNo;
  char name[20];// max name length
  float cgpa;
  while(!fin.eof()){
    fin >> rollNo;
    fin >> name;
    fin >> cgpa;
    //cout << rollNo << " " << name << " " << cgpa << endl;
    avl_tree.insertStudent(rollNo,name,cgpa);
  }
  avl_tree.inorderPrintStudentRollNumbers();
  
}
