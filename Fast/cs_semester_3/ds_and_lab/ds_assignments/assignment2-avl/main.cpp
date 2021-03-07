// compile command: g++ main.cpp
// L19-1196 3E2
#include<iostream>
#include "containers.h"
#include "containers.cpp" // AVL etc
//added because template declaration
// and definitions should be at one place
#include "solutions.cpp" // Q1 to Q5 functions
int main(){
  //===============================
  cout << "Testing Q1/a: started ...\n";
  TreeNode<int>* node1 = new TreeNode<int>(1);
  TreeNode<int>* node2 = new TreeNode<int>(2);
  TreeNode<int>* node3 = new TreeNode<int>(3);
  TreeNode<int>* node4 = new TreeNode<int>(4);
  TreeNode<int>* node5 = new TreeNode<int>(5);

  node1->lChild = node3;
  node1->rChild = node2;
  node2->lChild = node5;
  node2->rChild = node4;

  BinaryTree<int> * unusual_tree = new BinaryTree<int>();
  unusual_tree->setRoot(node1);
  cout << "Before mirror\n";
  unusual_tree->inorderPrint();
  cout << endl;
  cout << "After taking mirror and inorder print\n";
  unusual_tree = mirror_iterative(unusual_tree);
  unusual_tree->inorderPrint();
    cout << endl;
  cout << "Q1/a ended...\n";
  //===============================
  cout << "Testing Q1/b: started ...\n";
  BinaryTree<int> * original_tree = mirror_iterative(unusual_tree);
  cout << "spiral printing...\n";
  spiral_print(original_tree);
  cout << endl;
  cout << "Q1/B ended...\n";
  //===============================
  BinaryTree<int>* tree2 = new BinaryTree<int>();
  tree2->insert(6);
  tree2->insert(4);
  tree2->insert(8);
  tree2->insert(2);
  tree2->insert(5);
  cout << "Diameter of tree2 is: " << diameterOfBinaryTree(tree2);
  cout << "Q3/a ended...\n";
  //===============================
  cout << "let us flatten BinaryTree... tree2\n";
  // it flattens all nodes as it is
  // it does not copy data
  // rather, Binary tree is flattened in real way
  LinkList<TreeNode<int>*> *l1;
  l1 = flatten(tree2);
  Node<TreeNode<int>*> *temp = l1->getHead();
  while(temp != NULL){
    temp->data->print();
    temp = temp->next;
  }
  //===============================
  cout << "Q5/a joining two AVL Tree\n";
  AVL<int> a1;
  a1.insert(1);
  a1.insert(2);
  a1.insert(3);
  a1.insert(5);
  a1.insert(4);
  a1.insert(6);
  a1.insert(7);
  a1.insert(8);
  a1.insert(9);
  a1.insert(20);
  a1.insert(19);
  a1.insert(17);
  a1.insert(18);
  cout << "inorder print T1: ";
  a1.inorderPrint();
  cout << endl;
  cout << "spiral print T1: ";
  spiral_print(&a1);
  cout << endl;

  AVL<int> a2;
  a2.insert(100);
  a2.insert(50);
  a2.insert(70);
  a2.insert(30);
  a2.insert(21);
  a2.insert(90);
  cout << "spiral print T2: ";
  spiral_print(&a2);
  cout << endl;
  cout << "inorder print T2: ";
  a2.inorderPrint();
  cout << endl;

  AVL<int> *a3 = join(&a1,&a2);
  cout << "after merging...\n";
  cout << "inorder print T3\n";
  a3->inorderPrint();
  cout << endl;
  cout << "spiral print T3\n";
  spiral_print(a3);

  delete node1;
  delete node2;
  delete node3;
  delete node4;
  delete node5;
  delete unusual_tree;
  delete tree2;

  return 0;
  }


