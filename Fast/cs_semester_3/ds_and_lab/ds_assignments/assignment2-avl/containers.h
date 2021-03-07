// it contains all containers
// stack, binary tree, linked list
// code of assignment # 1 written by me
#ifndef _CONTAINERS_H
#define  _CONTAINERS_H

#include <iostream>
using namespace std;

template <typename TYPE> 
class Node{
public:
  TYPE data;
  Node* next;

  Node();
  Node(int data);
  void print();
  ~Node();
};
//-------------------------------------
template <typename TYPE> 
class LinkList{
private:
  Node<TYPE>* head;
  Node<TYPE>* tail;
public:
  LinkList();
  void setHead(Node<TYPE>*ptr);
  Node<TYPE> * getHead();
  Node<TYPE> * getTail();
  Node<TYPE> * getNthNode(int n); // returns nth node
  int getLength();
  void insertAtStart(TYPE const element);
  void insertAtEnd(TYPE const element);
  bool search(TYPE const& element) const;
  void insertAfter(TYPE const v1, TYPE const v2);
  void deleteFromFront();
  void deleteAtEnd();
  void deleteAllOccurrences(TYPE v1);
  void print() const;
  //------------------------------ miscellenous functions 
  ~LinkList();
};

template <typename TYPE>
class Stack{
protected:
  LinkList<TYPE>* stack;
public:
  Stack();
  void push(TYPE element);
  TYPE pop();
  TYPE peek();
  bool isEmpty();
  ~Stack();
};

template <typename TYPE>
class Queue: public Stack<TYPE>{
  // Queue is almost stack with minor differnce
  // only functions will be overridden
public:
  Queue();
  TYPE pop();
  TYPE peek();
};

// //-------------------------------------
// template <typename TYPE>
// void reverseLinkList(LinkList<TYPE> & linked_list);
// //======================== end of prototype


// template <typename TYPE>
// void reverseLinkList(LinkList<TYPE> &linked_list){
//   // count the elements
//   // make a list of addresses of nodes in a linked list
//   // then point nodes to address in reverse orders
//   int total_nodes =0;
//   Node<TYPE>* current_ptr = linked_list.getHead();
//   while(current_ptr != NULL) {
//     current_ptr = current_ptr->next;
//     total_nodes++;
//   }

//   // total nodes have been calculated
//   Node<TYPE>**nodes = new Node<TYPE>*[total_nodes];
//   //now copy addresses into array
//   current_ptr = linked_list.getHead(); // reset current ptr
//   for(int i=0; i< total_nodes; i++){
//     nodes[i] = current_ptr;
//     current_ptr = current_ptr->next;
//   }
//   for(int i=total_nodes-1; i > 0; i--){
//     nodes[i]->next = nodes[i-1];
//   };
//   nodes[0]->next = NULL;
//   linked_list.setHead(nodes[total_nodes-1]);
// }

//=================== BinaryTree
template <typename TYPE>
class TreeNode{
  public:
  TYPE data;
  int height;
  TreeNode<TYPE>* lChild;
  TreeNode<TYPE>* rChild;
  TreeNode();
  TreeNode(TYPE data);
  void print();
  ~TreeNode(); // making base class polymorphic
};

template <typename TYPE>
class BinaryTree: public TreeNode<TYPE>{
protected:
  TreeNode<TYPE>* root;
  void inorder(TreeNode<TYPE>* root);
  TreeNode<TYPE>* preorder(TreeNode<TYPE>* root);
  void destroy_all_nodes(TreeNode<TYPE>* root);
public:
  BinaryTree();
  BinaryTree(TreeNode<TYPE>* root);
  TreeNode<TYPE>* getRoot();
  void setRoot(TreeNode<TYPE>*);
  void swap_children(TreeNode<TYPE>* parent);
  // will swap two child, left goes right and vice versa
  bool find(TYPE element);
  void insert(TYPE _data);
  void inorderPrint();
  ~BinaryTree();
};

template <typename TYPE>
class AVL: public BinaryTree<TYPE>{
public:
  AVL();
  void insert(TYPE element);
  bool ll_unbalance(TreeNode<TYPE>* pivot);
  bool rr_unbalance(TreeNode<TYPE>* pivot);
  bool lr_unbalance(TreeNode<TYPE>* pivot);
  bool rl_unbalance(TreeNode<TYPE>* pivot);
    
  void ll_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* to_be_balanced); // parent of pivot node
  void rr_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* to_be_balanced); // parent of pivot node
  void lr_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* to_be_balanced); // parent of pivot node
  void rl_rotation(TreeNode<TYPE>* parent,TreeNode<TYPE>* pivot,Stack<TreeNode<TYPE>*>* to_be_balanced); // parent of pivot node

  //base class destructor is running
};
//==================== AVLTree
#endif
