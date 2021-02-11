#include <iostream>
#include "matrix.h"
using namespace std;
template <class T>
Matrix<T>::Matrix(){
  this->matrix = NULL;
  rows=0;
  cols = 0;
}
template <class T>
Matrix<T>::Matrix(int rows, int cols){
  // rol cols constructor called
  matrix = new T* [rows];
  for(int i=0; i< rows; i++) matrix[i] = new T[cols];
  this->rows = rows;
  this->cols = cols;
}

template <class T>
Matrix<T>::Matrix(const Matrix &obj){
  this->rows = obj.rows;
  this->cols = obj.cols;
  this->matrix = new T* [this->rows];
  for(int i=0; i< this->rows; i++){
    this->matrix[i] = new T [this->cols];
  }
  for(int i=0; i< this->rows; i++){
    for(int j=0; j< this->cols; j++){
      T element = obj.getElement(i,j);
      this->insertElement(element,i,j);
      }
  }
}

template <class T>
int Matrix<T>::getNoOfRows() const {return this->rows;}
template <class T>
int Matrix<T>::getNoOfCols() const {return this->cols;}

template <class T>
T Matrix<T>::getElement(int row, int col) const{
  return matrix[row][col];
}

template <class T>
void Matrix<T>::insertElement(T const &element, int rowNo, int colNo){
  if(rows >= rowNo && cols >= colNo){
    matrix[rowNo][colNo] = element;
  }
  else{
    cout << "index out of range \n";
  }
}

template <class T>
void Matrix<T>::print(){
  for(int i=0; i< rows; i++){
    for(int j=0; j < cols; j++){
      cout << this->matrix[i][j] << " ";
	}
    cout << "\n";
  }
}

template <class T>
void Matrix<T>::transpose(){
  T **temp_matrix = new T*[cols];
  for(int i=0; i < cols; i++){
    temp_matrix[i] = new T[rows];
  }
  // now fill the values
  for(int i=0; i< cols; i++){
    for(int j=0; j < rows; j++){
      temp_matrix[i][j] = matrix[j][i];

    }
  }
  //------------- delete old matrix
  for(int i=0; i< rows; i++){
    delete[]matrix[i];
  }
  //------------ now point matrix to temp_matrix
  matrix = temp_matrix;
  int temp_rows = this->rows;
  this->rows = cols;
  this->cols =temp_rows;
}

template <class T>
Matrix& Matrix<T>::operator+ (const Matrix & obj){
  if(this->rows == obj.getNoOfRows() && this->cols == obj.getNoOfCols()){
    Matrix *m = new Matrix(this->rows, this->cols);
    for(int i=0; i< this->rows; i++){
      for(int j=0; j< this->cols; j++){
	T element = this->getElement(i,j)+obj.getElement(i,j);
	m->insertElement(element,i,j);
      }
    }
    return *m;
  }
  else{
    cout << "addition is not possible as there are different dimensions \n";
  }
}

template <class T>
void Matrix<T>::operator = (const Matrix &obj){
  if(this != &obj){
    this->rows = obj.rows;
    this->cols = obj.cols;
    this->matrix = new T*[this->rows];
    for(int i=0; i < this->rows; i++){
      this->matrix[i] = new T [this->cols];
    }
    // now assign correspinding values
    for(int i=0; i< this->rows; i++){
      for(int j=0; j< this->cols; j++){
	T element = obj.getElement(i,j);
	//this->matrix[i][j] = obj.matrix[i][j];
	this->insertElement(element,i,j);
      }
  }
}
}

//------------
template <class T>
Matrix<T>::~Matrix(){
  if(this->rows !=0){
    for(int i=0; i< this->rows; i++) delete []matrix[i];
    delete matrix;
    matrix = NULL;
  }
}
