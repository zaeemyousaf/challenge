#include "min_heap.h"
#include <iostream>
using namespace std;

 
MinHeap::MinHeap(){
  // default constructor
  arr = new HNode[1];
  capacity = 1;
  totalItems =0;
  //cout << "defalut constructor\n";
}

 
MinHeap::MinHeap(int _capacity){
  arr = new HNode[_capacity];
  capacity = _capacity;
  totalItems =0;
  //cout << "parametrized called\n";
}
 
void MinHeap::insert_node(HNode parent){
  if(totalItems < capacity){
    // there is space
    arr[totalItems] = parent;
    totalItems++;
  }
  else{
    // grow double and insert
    grow_double();
    arr[totalItems] = parent;
    totalItems++;
  }
  //cout << "index: " << totalItems << endl;
  adjust(totalItems,(totalItems)/2);
}

 
void MinHeap::grow_double(){
  int new_capacity = capacity*2;
  HNode *new_arr = new HNode[new_capacity];
  for(int i=0; i< capacity; i++){
    // copy old array into new_array
    new_arr[i] = arr[i];
  }
  if(arr != NULL) delete []arr;
  arr = new_arr;
  capacity = new_capacity;  
}
 
void MinHeap::adjust(int cindex,int pindex){
  if(pindex !=0 && arr[cindex-1].freq < arr[pindex-1].freq){    
    //cout << "adjusting ...\n";
    // HNode parent = arr[pindex];
    // HNode child = arr[pindex];

    HNode temp = arr[pindex-1];
    arr[pindex-1] = arr[cindex-1];
    arr[cindex-1] = temp;
    
    cindex = pindex;
    pindex = pindex/2;
    adjust(cindex,pindex);
  }
  return;
}


 
HNode* MinHeap::getMin(){
  return &arr[0];
}
 
void MinHeap::deleteMin(){  
  arr[0] = arr[totalItems-1];
  totalItems = totalItems-1;
  // now hepify
  for(int i=0; 2*i+2 <= totalItems; i++){
    int gc = arr[2*i+1].freq < arr[2*i+2].freq ? 2*i+1 : 2*i+2;
    if(arr[i].freq > arr[gc].freq){
      // if parent < greatest children then swap
      HNode temp = arr[i];
      arr[i] = arr[gc];
      arr[gc] = temp;
    }
  }
} 
 
bool MinHeap::isEmpty()const{
  if(totalItems >0) return false;
  return true;
}

 
int MinHeap::size(){
  return totalItems;
}

 
void MinHeap::print(){
  for(int i=0; i < totalItems; i++){
    cout << arr[i].freq << ": " << arr[i].character << "\n";
  }
}
 
MinHeap::~MinHeap(){
  delete []arr;
  //cout << "heap destroyed...\n";
}
//------------------
Huffman::Huffman(){
  char_list  = new MinHeap();
}

void Huffman::insert(int _freq, char _character){
  //HNode *temp = new HNode(_freq,_character);
  HNode temp(_freq,_character);
  char_list->insert_node(temp);
}

void Huffman::makeTree(){
  //char_list->print();
  while(char_list->size() > 1){
    HNode *left = new HNode(*char_list->getMin());
    char_list->deleteMin();
    HNode *right = new HNode(*char_list->getMin());
    char_list->deleteMin();
    // cout << "------------------\n";
    // cout << left->freq << ": " << left->character << endl;
    // cout << right->freq << ": " << right->character << endl;
    //    cout << "------------------\n";
    HNode parent(left->freq+right->freq,' ');
    parent.left = left;
    parent.right = right;
    char_list->insert_node(parent);
  }
}

void Huffman::inorder(HNode *root, char *code, int &index){
  if(root->left == NULL && root->right == NULL){
    //cout << root->freq << ": " <<  root->character << endl;
    cout << root->character << ": " << root->freq << " ";
    cout << code << endl;
    index = index-1;
    code[index] = '\0';
    return;
  }

  if(root->left != NULL){
    code[index++] = '0';
    code[index] = '\0';
  }

  inorder(root->left,code,index);
  //cout << root->freq << "<- freq \n ";
  if(root->right != NULL){
    code[index++] = '1';
    code[index] = '\0';
  }

  inorder(root->right,code,index);
  index = index-1;
  code[index] = '\0';
}
void Huffman::printHuffman(){
  HNode *root = char_list->getMin();
  char huffman_code[20];
  int index=0;
  inorder(root,huffman_code,index);
}
