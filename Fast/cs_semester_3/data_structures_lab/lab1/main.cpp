#include <iostream>
#include "matrix.h"
using namespace std;
int main(){
  Matrix<int> m1(2,3);
  m1.insertElement(1, 0, 0); m1.insertElement(1, 0, 1); m1.insertElement(1, 0, 2); m1.insertElement(0, 1, 0); m1.insertElement(0, 1, 1); m1.insertElement(0, 1, 2);

  m1.transpose();
  Matrix<int> m2(2,3);
  m2.insertElement(-1, 0, 0); m2.insertElement(-1, 0, 1); m2.insertElement(-1, 0, 2); m2.insertElement(10, 1, 0); m2.insertElement(5, 1, 1); m2.insertElement(1, 1, 2);
  m2.transpose();

  m1.print();
  cout << "===================\n";
  m2.print();
  cout << "===================\n";
  Matrix<int> m3 = (m1+m2);
  m3.print();
}
