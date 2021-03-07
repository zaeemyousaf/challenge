#include "min_heap.h"
#include "min_heap.cpp"
#include <iostream>
#include <fstream>
Huffman createHuffman(const char *filename);
using namespace std;
int main(){
  Huffman h2 = createHuffman("file.txt");
  h2.printHuffman();

  getchar();
  return 0;
}

Huffman createHuffman(const char *filename){
  Huffman h1;
  char character;
  int frequency;
  ifstream fin(filename);
  
  while(! fin.eof()){
    fin >> character;
    fin >> frequency;
    //cout << character << frequency << endl;
    h1.insert(frequency,character);    
  }
  h1.makeTree();
  return h1;
}
