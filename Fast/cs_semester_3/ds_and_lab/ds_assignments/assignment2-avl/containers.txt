#include "containers.h"
#include <iostream>
using namespace std;
int bigger(int a, int b){
  if (a > b) return a;
  else return b;
}
//================== class Node
template <typename TYPE>
Node<TYPE>::Node(){
  next = NULL;
}
//-------------------------------------
template <typename TYPE>
Node<TYPE>::Node(int data){
  this->data = data;
  this->next=NULL;
    
}
//-------------------------------------
template <typename TYPE>
void Node<TYPE>::print(){
  cout << "data: " << data << endl;
  if(next !=NULL){
    cout << "next: " << next << endl;
  }
  else{
    cout << "next: " << endl;
  }
}
template <typename TYPE>
Node<TYPE>::~Node(){
}
//======================= class LinkList
template <typename TYPE>
LinkList<TYPE>::LinkList(){
  // make one node
  head = NULL;
  tail = NULL;

}

template <typename TYPE>
bool LinkList<TYPE>::search(TYPE const& v) const{
  Node<TYPE>* current_ptr = head;
  bool found=false;
  while(current_ptr != NULL && found !=true){
    if(current_ptr->data == v) found=true;
    current_ptr = current_ptr->next;
  }
  return found;
}

template <typename TYPE>
void LinkList<TYPE>::setHead(Node<TYPE> *ptr){
  head = ptr;
}

//----------------------------------------
template <typename TYPE>
Node<TYPE> * LinkList<TYPE>::getHead(){
  return head;
}

template <typename TYPE>
Node<TYPE> * LinkList<TYPE>::getTail(){
  return tail;
}

//----------------------------------------
template <typename TYPE>
Node<TYPE> * LinkList<TYPE>::getNthNode(int n){
  Node<TYPE> * current = NULL;
  if(n > 0){
    current = head;
    int counter=1;
    while(current != NULL && counter < n){
      current = current->next;
      counter++;
    }
    return current;
  }
  else{
    return current;
  }
}

template <typename TYPE>
int LinkList<TYPE>::getLength(){
  if(head != NULL){
    int counter=0;
    // traverse the list
    Node<TYPE>* current = head;
    while(current != NULL){
      current = current->next;
      counter++;
    }
    return counter;
  }
  else{return 0;}
}
//----------------------------------------
template <typename TYPE>
void LinkList<TYPE>::insertAtStart(TYPE const element){
  Node<TYPE> *temp_node = new Node<TYPE>();
  temp_node->data = element;
  temp_node->next = head;
  head = temp_node;
}

template <typename TYPE>
void LinkList<TYPE>::insertAtEnd(TYPE const element){
  Node<TYPE>*temp_node = new Node<TYPE>();
  temp_node->data = element;
  temp_node->next = NULL;
  if(head != NULL){
    // traverse the list
    Node<TYPE>* current = head;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = temp_node;
    tail = temp_node;
  }
  else{
    head = temp_node;
    tail = temp_node;
  }
}

template <typename TYPE>
void LinkList<TYPE>::deleteFromFront(){
  if(head != NULL){
    Node<TYPE>* toBeDeleted = head;
    head = head->next;
    delete toBeDeleted;
    toBeDeleted = NULL;
  }
}

template <typename TYPE>
void LinkList<TYPE>::deleteAtEnd(){
  if(head == NULL){
    // do nothing
  }
  else if(head->next == NULL){
    // only one node
    delete head;
    head = NULL;
    tail = NULL;
  }
  else{
    Node<TYPE>* toBeDeleted = head;
    Node<TYPE>* previous_node;
    while(toBeDeleted->next !=NULL){
      previous_node = toBeDeleted;
      toBeDeleted = toBeDeleted->next;
    }
    delete toBeDeleted;
    previous_node->next = NULL;
    tail = previous_node;
  }
}

template <typename TYPE>
void LinkList<TYPE>::print() const{
  Node<TYPE>* current_ptr = head;
  while(current_ptr != NULL){
    cout << current_ptr->data << "->";
    current_ptr= current_ptr->next;
  }
  cout << endl;
}

template <typename TYPE>
LinkList<TYPE>::~LinkList(){
  Node<TYPE>* current_ptr = head;
  Node<TYPE>* temp_ptr;
  while(current_ptr != NULL){
    temp_ptr = current_ptr->next;
    delete current_ptr;
    current_ptr= temp_ptr;
  }
}
//======================= class Stack
template <class TYPE>
Stack<TYPE>::Stack(){
  stack = NULL;
  stack = new LinkList<TYPE>();
}

template <class TYPE>
void Stack<TYPE>::push(TYPE element){
  stack->insertAtEnd(element);
}

template <class TYPE>
TYPE Stack<TYPE>::pop(){
  if(!isEmpty()){
    TYPE value = peek();
    stack->deleteAtEnd();
    return value;
  }
}

template <class TYPE>
bool Stack<TYPE>::isEmpty(){
  if(stack->getHead()){
    return false;
  }
  else {return true;}
}
template <class TYPE>
TYPE Stack<TYPE>::peek(){
  if(!isEmpty())
    return (stack->getTail())->data;
  else{
    cout << "\nerror: stack underflow";
  }
}
template <class TYPE>
Stack<TYPE>::~Stack(){
  while(stack->getHead()) stack->deleteAtEnd();
}
//-------------------------------------

template <class TYPE>
Queue<TYPE>::Queue(): Stack<TYPE>(){}


template <class TYPE>
TYPE Queue<TYPE>::pop(){
  if(! Stack<TYPE>::isEmpty()){
    TYPE value = peek();
    Stack<TYPE>::stack->deleteFromFront();
    return value;
  }
}

template <class TYPE>
TYPE Queue<TYPE>::peek(){
  if(! Stack<TYPE>::isEmpty())
    return (Stack<TYPE>::stack->getHead())->data;
  else{
    cout << "\nerror: stack underflow";
  }
}
//===================== class TreeNode
template <typename TYPE>
TreeNode<TYPE>::TreeNode(){
  height=0;
  lChild = NULL;
  rChild = NULL;
}
template <typename TYPE>
TreeNode<TYPE>::TreeNode(TYPE data){
  height=0;
  this->data = data;
  lChild = NULL;
  rChild = NULL;
}

template <class TYPE>
int get_height(TreeNode<TYPE>* node){
  if(node != NULL){
    return 1 + bigger(get_height(node->lChild), get_height(node->rChild)); 
  }
  else return 0;
}

template <typename TYPE>
void TreeNode<TYPE>::print(){
  // will be helpful as polymorphic
  cout << data << "->";
}

template <typename TYPE>
TreeNode<TYPE>::~TreeNode(){
  // nothing to do
}
//================== class BinaryTree
template <class TYPE>
BinaryTree<TYPE>::BinaryTree(){
  root = NULL;
}

template <class TYPE>
BinaryTree<TYPE>::BinaryTree(TreeNode<TYPE>* _root){
  root = _root;
}

template <class TYPE>
TreeNode<TYPE>* BinaryTree<TYPE>::getRoot(){
  return root;
}
template <class TYPE>
void BinaryTree<TYPE>::setRoot(TreeNode<TYPE>* _root){
  root = _root;
}

template <class TYPE>
void swap_children(TreeNode<TYPE>* parent){
  
  if(parent->lChild != NULL || parent->rChild != NULL){
    // has at least one child
    TreeNode<TYPE>* temp = parent->lChild;
    parent->lChild = parent->rChild;
    parent->rChild = temp;
  }
  // else no need to swap null child
}

template <class TYPE>
void BinaryTree<TYPE>::insert(TYPE element){
  TreeNode<TYPE> *node= new TreeNode<TYPE>();
  node->data = element;
  node->lChild = NULL;
  node->rChild = NULL;
  
  if(root == NULL){
    root = node;
  }
  else{
    TreeNode<TYPE> *node_index = root;
    TreeNode<TYPE> *leaf_node = root;
    while(node_index != NULL){
      
      if(element > node_index->data){
	// follow right
	//cout << "following right \n";
	leaf_node = node_index;
	node_index = node_index->rChild;
      }
      else{
	// follow left
	//cout << "following left\n";
	leaf_node = node_index;
	node_index = node_index->lChild;
      }
    }
    //insert node_index here
    if(element > leaf_node->data){
      leaf_node->rChild = node;
      //cout << "added node on right...\n";
    }
    else{
      //cout << "added node on left...\n";
      leaf_node->lChild = node;
    }    
  }
}

template <typename TYPE>
bool BinaryTree<TYPE>::find(TYPE element){
  TreeNode<TYPE>* node_index = root;
  while(node_index != NULL){
    int node_value = node_index->data;
    if(element == node_value){
      return true;
    }
    else if(element > node_value){
      // follow right
      node_index = node_index->rChild;
    }
    else{
      // follow left
      node_index = node_index->lChild;
    }
  }
  return false;
}

template <class TYPE>
void BinaryTree<TYPE>::inorder(TreeNode<TYPE> *root_ptr){
  if(root_ptr == NULL){
    return;
  }
  else{
    //cout << "before lChild" << endl;
    inorder(root_ptr->lChild);
    cout << root_ptr->data << " ";
    //cout << root_ptr->data << " :" << root_ptr->height << endl;
    //cout << "balance factor: " << root_ptr->balance << endl;
    inorder(root_ptr->rChild);
    //cout << "after rChild" << endl;
    //cout <<  "going to traverse right " << root_ptr << endl;
  }
  //cout << "total diameter: " << left+right << endl;
}
//---------------------
template <class TYPE>
void BinaryTree<TYPE>::inorderPrint(){
  if(root !=NULL)
    inorder(root);
}

template <class TYPE>
void BinaryTree<TYPE>::destroy_all_nodes(TreeNode<TYPE> *root){
  if(root == NULL){
    return;
  }
  destroy_all_nodes(root->lChild);
  destroy_all_nodes(root->rChild);
  //cout << "deleting " << root->data->get_roll_no() << endl;
  delete root;
}

template <class TYPE>
BinaryTree<TYPE>::~BinaryTree(){
  // just a wrapper function to be called itself
  if(root != NULL){
    destroy_all_nodes(root);
  }
  //cout << "All nodes destroyed successully";
}
//================ AVL
template <typename TYPE>
AVL<TYPE>::AVL():BinaryTree<TYPE>(){}

template <typename TYPE>
void AVL<TYPE>::insert(TYPE element){
  TreeNode<TYPE>* node_index = BinaryTree<TYPE>::root;
  TreeNode<TYPE>* leaf_node = node_index;
  if(! BinaryTree<TYPE>::find(element)){
    TreeNode<TYPE>* new_node = new TreeNode<TYPE>(element);
    TreeNode<TYPE>* unbalanced_node = node_index;
    TreeNode<TYPE>* parent_unbalanced_node = node_index;
    Stack<TreeNode<TYPE>*> *balance_correction = new Stack<TreeNode<TYPE>*>();
    if(node_index != NULL){
      while(node_index != NULL){
	if(element > node_index->data){
	  // move right
	  node_index->height--;
	  if(node_index->height > 1 || node_index->height < -1){
	    //parent_unbalanced_node = unbalanced_node;
	    parent_unbalanced_node = balance_correction->pop();
	    unbalanced_node = node_index;
	  }
	  balance_correction->push(node_index);
	  leaf_node = node_index;
	  node_index = node_index->rChild;
	}
	else{
	  // move left
	  node_index->height++;
	  if(node_index->height > 1 || node_index->height < -1){
	    parent_unbalanced_node = balance_correction->pop();
	    unbalanced_node = node_index;
	  }
	  balance_correction->push(node_index);
	  leaf_node = node_index;
	  node_index = node_index->lChild;
	}
      }
      // we are at leaf node
      if(element > leaf_node->data){
	leaf_node->rChild = new_node;
      }
      else{
	leaf_node->lChild = new_node;
      } 
    }
    else{
      BinaryTree<TYPE>::root = new_node;
    }

    if(unbalanced_node != NULL){
      //----------------- perform rotations
      if(ll_unbalance(unbalanced_node)){
	//cout << "left left dectected ...\n";	
	// perform rr_rotation
	rr_rotation(parent_unbalanced_node,unbalanced_node,balance_correction);
      }
      else if(rr_unbalance(unbalanced_node)){
	//cout << "right right dectected ...\n";	
	// perform ll_rotation
	ll_rotation(parent_unbalanced_node,unbalanced_node,balance_correction);
	// if(parent_unbalanced_node != NULL) cout << "parent: " << parent_unbalanced_node->data << endl;
	//cout << "unbalanced node: " << unbalanced_node->data << endl;
	// cout << "parentnode: " << parent_unbalanced_node->data << endl;
      }

      else if(lr_unbalance(unbalanced_node)){
	//cout << "left right detected ...\n";
	// perform rl_rotation
	rl_rotation(parent_unbalanced_node,unbalanced_node,balance_correction);
      }
      else if(rl_unbalance(unbalanced_node)){
	//cout << "right left dected ...\n";
	// perform lr_rotation
lr_rotation(parent_unbalanced_node,unbalanced_node,balance_correction);
      }
      //----------------- end of rotations
    }

  }
  else{
    // else, duplicate values not allowed
    cout << "ignoring duplicate values...\n";
  }
}

//------------------
template <typename TYPE>
bool AVL<TYPE>::ll_unbalance(TreeNode<TYPE>* pivot){
  if(pivot != NULL && pivot->lChild != NULL){
    if(pivot->height == 2 && pivot->lChild->height == 1) return true;
  }
  return false;
}
//------------------
template <typename TYPE>
bool AVL<TYPE>::rr_unbalance(TreeNode<TYPE>* pivot){
  if(pivot != NULL && pivot->rChild != NULL){
    if(pivot->height == -2 && pivot->rChild->height == -1) return true;
  }
  return false;
}
//------------------
template <typename TYPE>
bool AVL<TYPE>::lr_unbalance(TreeNode<TYPE>* pivot){
  if(pivot != NULL && pivot->lChild != NULL){
    if(pivot->height == 2 && pivot->lChild->height == -1) return true;
  }
  return false;
}
//------------------
template <typename TYPE>
bool AVL<TYPE>::rl_unbalance(TreeNode<TYPE>* pivot){
  if(pivot != NULL && pivot->rChild != NULL){
    if(pivot->height == -2 && pivot->rChild->height == 1) return true;
  }
  return false;
}

//--------------------
template <typename TYPE>
void AVL<TYPE>::ll_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* balance_correction){
  TreeNode<TYPE>* child = pivot->rChild;
  TreeNode<TYPE>* child_left = child->lChild;
  child->lChild = NULL;  

 //cout << "trying to rotate left left \n";

  if(parent != NULL){
    //cout << "parent: " << parent->data << " " << endl;
    if(parent->lChild == pivot){
      child = pivot->rChild;
      parent->lChild = child;
      parent->height = get_height(parent->lChild)-get_height(parent->rChild);

    }
    else{
    parent->rChild = child;
    parent->height = get_height(parent->lChild)-get_height(parent->rChild);
    }
  }

  pivot->rChild = NULL;
  child->lChild = pivot;
  pivot->rChild = child_left; 
  
    if(pivot == BinaryTree<TYPE>::root){
    // change root
      BinaryTree<TYPE>::root = child;
  }
    //  adjust balance factor
    
    while(! balance_correction->isEmpty()){
      TreeNode<TYPE>* temp;
      temp = balance_correction->pop();
      //cout << temp->data <<" balance correction performed\n";
      temp->height = get_height(temp->lChild)-get_height(temp->rChild);
    }
    TreeNode<TYPE>* temp_node = BinaryTree<TYPE>::root;
    while(temp_node != NULL){
      temp_node->height = get_height(temp_node->lChild)-get_height(temp_node->rChild);
      temp_node = temp_node->rChild;
    }
}

template <typename TYPE>
void AVL<TYPE>::rr_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* balance_correction){
  TreeNode<TYPE>* child = pivot->lChild;
  TreeNode<TYPE>* child_right = child->rChild;
  child->rChild = NULL;  
  if(parent != NULL){
    //cout << "parent: " << parent->data << " " << endl;
    if(parent->rChild == pivot){
    parent->rChild = child;
    parent->height = get_height(parent->lChild)-get_height(parent->rChild);

    }
    else{
    parent->lChild = child;
    parent->height = get_height(parent->lChild)-get_height(parent->rChild);
    }
  }

  //cout << "trying to rotate left left \n";
  pivot->lChild = NULL;
  child->rChild = pivot;
  pivot->lChild = child_right;
    if(pivot == BinaryTree<TYPE>::root){
    // change root
      BinaryTree<TYPE>::root = child;
  }
    //  adjust balance factor
    while(! balance_correction->isEmpty()){
      TreeNode<TYPE>* temp;
      temp = balance_correction->pop();
      temp->height = get_height(temp->lChild)-get_height(temp->rChild);
    }
        TreeNode<TYPE>* temp_node = BinaryTree<TYPE>::root;
    while(temp_node != NULL){
      temp_node->height = get_height(temp_node->lChild)-get_height(temp_node->rChild);
      temp_node = temp_node->rChild;
    }

}

template <typename TYPE>
void AVL<TYPE>::rl_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* balance_correction){
  // for lr_unbalance
  TreeNode<TYPE>* child = pivot->lChild;
  TreeNode<TYPE>* grand_child = child->rChild;
  TreeNode<TYPE>* grand_child_left = grand_child->lChild;
  TreeNode<TYPE>* grand_child_right = grand_child->rChild;

  grand_child->rChild= pivot;
  pivot->lChild = grand_child_right;
  grand_child->lChild = child;
  child->rChild = grand_child_left;

  if(parent == NULL) {
    BinaryTree<TYPE>::root = grand_child;
  }
  else if(parent->lChild == pivot) parent->lChild = grand_child;
  else if(parent->rChild == pivot) parent->rChild = grand_child;
    //  adjust balance factor
    while(! balance_correction->isEmpty()){
      //cout << "coming here...";
      TreeNode<TYPE>* temp;
      temp = balance_correction->pop();
      temp->height = get_height(temp->lChild)-get_height(temp->rChild);
    }
        TreeNode<TYPE>* temp_node = BinaryTree<TYPE>::root;
    while(temp_node != NULL){
      temp_node->height = get_height(temp_node->lChild)-get_height(temp_node->rChild);
      temp_node = temp_node->rChild;
    }

}


template <typename TYPE>
void AVL<TYPE>::lr_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* balance_correction){
  // for rl_unbalace
  TreeNode<TYPE>* child = pivot->rChild;
  TreeNode<TYPE>* grand_child = child->lChild;
  TreeNode<TYPE>* grand_child_left = grand_child->lChild;
  TreeNode<TYPE>* grand_child_right = grand_child->rChild;

  grand_child->lChild= pivot;
  pivot->rChild = grand_child_left;
  grand_child->rChild = child;
  child->lChild = grand_child_right;
    if(parent == NULL) {
    BinaryTree<TYPE>::root = grand_child;
  }
  else if(parent->lChild == pivot) parent->lChild = grand_child;
  else if(parent->rChild == pivot) parent->rChild = grand_child;
    //  adjust balance factor    
    while(! balance_correction->isEmpty()){
      //cout << "coming here...";
      TreeNode<TYPE>* temp;
      temp = balance_correction->pop();
      temp->height = get_height(temp->lChild)-get_height(temp->rChild);
    }
        TreeNode<TYPE>* temp_node = BinaryTree<TYPE>::root;
    while(temp_node != NULL){
      temp_node->height = get_height(temp_node->lChild)-get_height(temp_node->rChild);
      temp_node = temp_node->rChild;
    }
}
