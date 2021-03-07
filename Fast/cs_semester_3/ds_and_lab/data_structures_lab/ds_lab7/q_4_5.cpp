#include <iostream>
#include "linklist.h"
// LinkList class was taken from my previous lab
// insertAtTail
// print
// merge
// are  made recursive

int main(){
  LinkList<int> l1;
  LinkList<int> l2;
  Node<int>* head = NULL;
  Node<int>* head1 = NULL;
  
  head = l1.insertAtTail(8,head);
  head = l1.insertAtTail(7,head);
  head = l1.insertAtTail(6,head);
  head = l1.insertAtTail(0,head);
  l1.print(head);
  cout << "\n";
  head1 = l2.insertAtTail(9,head1);
  head1 = l2.insertAtTail(2,head1);
  head1 = l2.insertAtTail(1,head1);
  l2.print(head1);

  retun 0;
}
