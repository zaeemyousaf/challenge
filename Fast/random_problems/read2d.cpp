// for Muhammad Ahmad
// reads 2D array from file
// allocates dynamic memory
// stores them there and reads

#include <iostream>
#include <fstream>
using namespace std;
int main(){
  ifstream f("data.txt");
  int rows;
  int cols;
  f >> rows;
  f >> cols;

  int** matrix = new int* [rows];
  for(int i=0; i< rows; i++){
    matrix[i] = new int [cols];
  }

  // start reading the file
  for(int i=0; i< rows; i++){
    for(int j=0; j< cols; j++){
    f >> matrix[i][j];
    }
  }
  // now print the array
  for(int i=0; i< rows; i++){
    for(int j=0; j< cols; j++){
      cout << matrix[i][j] << " ";
  }
    cout << endl;
    }

  return 0;
}

