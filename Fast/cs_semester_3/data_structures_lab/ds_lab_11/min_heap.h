#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include <iostream>
using namespace std;

struct HNode{
  int freq;
  char character;
  HNode *left, *right;
  HNode(){
    left = right = NULL;
    //cout << "defalult called\n";
  }
  HNode(int _freq, char _character){
    freq = _freq;
    character = _character;
    left = right = NULL;
    //cout << "parmeterized called\n";
  }
  HNode(const HNode &obj){    
    this->freq = obj.freq;
    this->character = obj.character;
    this->left = obj.left;
    this->right = obj.right;
    //cout << "copy called\n";
  }

  HNode &operator = (HNode &obj){
    if(&obj != this){
      this->freq = obj.freq;
      this->character = obj.character;
      this->left = obj.left;
      this->right = obj.right;
      //cout << "assignment called\n";
      return *this;
    }
  }

  void print(){
    cout << character << ": " << freq << endl;
  }
};

class MinHeap{
 private:
  HNode *arr;
  int capacity;
  int totalItems;
public:
  MinHeap();
  MinHeap(int _capacity);
  void insert_node(HNode parent);
  void grow_double();
  void adjust(int cindex,int pindex);
  // child index, parent index
  HNode* getMin();
  void deleteMin();
  bool isEmpty() const;
  int size();
  void print();
  ~MinHeap();
};

class Huffman{
private:
  MinHeap *char_list;
public:
  Huffman();
  void insert(int _freq, char _character);
  void insert_internal(HNode* parent);
  void makeTree();
  void mainteTree();
  void inorder(HNode *root, char *huffman_code, int &index);
  void printHuffman();
};
#endif
