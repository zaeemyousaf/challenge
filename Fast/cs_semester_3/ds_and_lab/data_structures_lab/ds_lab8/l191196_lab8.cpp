#include <iostream>
using namespace std;

template <typename k, typename v>
struct TNode{
  k key;
  v value;
  TNode<k, v> *leftChild;
  TNode<k, v> *rightChild;
  TNode();
};

template <typename k, typename v>
TNode<k,v>::TNode(){
  leftChild = NULL;
  rightChild = NULL;
}

template <typename k, typename v>
class BST{
private:
  TNode<k,v> *root;
  void copy_tree(TNode<k,v>* temp1, TNode<k,v>* temp2);
public:
  BST();
  BST(const BST<k,v> &btree);
  TNode<k,v>* get_root();
  void insert(k key, v value);
  v*  recursive_search(k key, TNode<k,v>* root);
  v* search(k value);
  void PrintNodes(TNode<k,v>* temp);
  void inorderPrintKeys();

  int length() const;
  void deleteKey(k key);
  ~BST();
};
//--------------
template <typename k, typename v>
BST<k,v>::BST(){
  root = NULL;
}

template <typename k, typename v>
BST<k,v>::BST(const BST<k,v> &btree){
  this->root = new TNode<k,v>();
  copy_tree(this->root,btree.root);
}
template <typename k, typename v>
void BST<k,v>::copy_tree(TNode<k,v>* temp1, TNode<k,v>* temp2) {
    temp1->key = temp2->key;
    temp1->value = temp2->value;
    if (temp2->leftChild != NULL) {
      temp1->leftChild = new TNode<k,v>();
      copy_tree(temp1->leftChild, temp2->leftChild);
    }
    if (temp2->rightChild != NULL) {
      temp1->rightChild = new TNode<k,v>();
      copy_tree(temp1->rightChild, temp2->rightChild);
    }
  }

template <typename k, typename v>
void BST<k,v>::insert(k key, v value){
  TNode<k,v>* new_node = new TNode<k,v>();
  new_node->key = key;
  new_node->value = value;
  if(root == NULL){
    // make it root
    root = new_node;
  }
  else{
    // add it into proper location
    TNode<k,v>* temp = root;
    TNode<k,v>* prev;
    while(temp != NULL){
      if(key > temp->key){
	// follow right
	prev = temp;
	temp = temp->rightChild;
      }
      else{
	//follow left
	prev = temp;
	temp = temp->leftChild;
      }
    }
    // attach here
    if(key > prev->key){
      prev->rightChild = new_node;
    }
    else{
      prev->leftChild = new_node;
    }
  }
}
//------------get_root
template <typename k, typename v>
TNode<k,v>* BST<k,v>::get_root(){
  return root;
}

template <typename k, typename v>
void BST<k,v>::PrintNodes(TNode<k,v>* temp) {
    if (temp->leftChild != NULL) {
      PrintNodes(temp->leftChild);
    }
    cout << temp->key << " ";
    if (temp->rightChild != NULL) {
      PrintNodes(temp->rightChild);
    }
}

template <typename k, typename v>
void BST<k,v>::inorderPrintKeys() {
    if (root == NULL) {
      cout << "tree is empty";
    }
    else if (root != NULL) {
      TNode<k,v>* temp = new TNode<k,v>;
      temp = this->root;
      if (temp->leftChild != NULL) {
	PrintNodes(temp->leftChild);
      }
      cout << root->key << " ";
      if (temp->rightChild != NULL) {
	PrintNodes(temp->rightChild);
      }
    }
}

template <typename k, typename v>
v* BST<k,v>::search(k value) {
    if (root == NULL) {
      return &root->value;
    }
    else if (root != NULL) {
      TNode<k,v>* temp = new TNode<k,v>();
      temp = this->root;
      return recursive_search(value, temp);
    }
  }

template <typename k, typename v>
v* BST<k,v>::recursive_search(k key, TNode<k,v>* root) {
    if (key == root->key) {
      return &root->key;
    }
    else if (key > root->key) {
      if (root->rightChild == NULL) {
	return NULL;
      }
      else if (root->rightChild != NULL) {
	return recursive_search(key, root->rightChild);
      }
    }
    else if (key <= root->key) {
      if (root->leftChild == NULL) {
	return NULL;
      }
      else if (root->leftChild != NULL) {
	return recursive_search(key, root->leftChild);
      }
    }
  }



//--------------
template <typename k, typename v>
BST<k,v>::~BST(){}
//--------------

int main(){
BST<int, int> tree; //the key and value both are of type int
tree.insert(500, 500);
tree.insert(1000, 1000);
tree.insert(1, 1);
tree.insert(600, 600);
tree.insert(700, 700);
tree.insert(10, 10);
tree.insert(30, 30);
tree.insert(9000, 9000);
tree.insert(50000, 50000);
tree.insert(20, 20);
BST<int, int> tree1(tree);
// tree1.deleteKey(20);
// tree1.deleteKey(500);
// tree1.deleteKey(1000);
 tree1.inorderPrintKeys();
 cout << endl << endl;
// cout<<"Tree1 Length: "<<tree1.length()<<endl;
 int *val = tree1.search(1);
 if (val != NULL)
 {
 cout << "1 found" << endl;
 }
 val = tree1.search(123);
 if (val == NULL)
 {
 cout << "123 not found" << endl;
 }
//system("pause");
 tree.inorderPrintKeys();
 cout << endl;
 tree1.inorderPrintKeys();
}
