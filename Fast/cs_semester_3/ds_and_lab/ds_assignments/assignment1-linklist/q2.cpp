#include <iostream>
#include "doublyLinkList.h" // ordinary methodes are defined there
// assignment methods are put in separate file
// for readability purpose
using namespace std;
int main(){

  DoublyLinkList <int> d1 = DoublyLinkList<int>();
  // <int> means: data type of 'node->data' is int
  d1.insertAtEnd(7);
  d1.insertAtEnd(9);
  d1.insertAtEnd(9);
  d1.insertAtEnd(10);
  cout << "list1 is ...\n";
  d1.print();

  DoublyLinkList <int> d2 = DoublyLinkList<int>();
  d2.insertAtEnd(70);
  d2.insertAtEnd(90);
  d2.insertAtEnd(100);
  d2.insertAtEnd(19);
  cout << "list2 is ...\n";
  d2.print();

  DoublyLinkList<int> d6;
  d6.concatenate(&d2,&d1); // also returns the address of list
  cout << "merging list1 and list2 unordered\n";
  d6.print();
  cout << "-------------------------\n";

  DoublyLinkList<int> d3;
  d3.concatenateOrdered(&d2,&d1); // also returns the address of list
  cout << "merging list1 and list2 ordered\n";
  d3.print();
  cout << "-------------------------\n";
  
  cout << "ans of two added char arrays\n";
  DoublyLinkList<char> d4;
  // <char> means: data type of 'node->data' is char
  d4.sumDoublyLinkList("10303030300303","10303030303030300");
  d4.print();
  cout << "-------------------------\n";
  
  cout << "going to add two integers\n";
  DoublyLinkList<int> d5;
  d5.sumDoublyLinkList(12020,202093);
  d5.print();
 
  return 0;

}
//----------------------------------- Q1 (a)
template <class TYPE>
DoublyLinkList<TYPE>* DoublyLinkList<TYPE>::concatenate(DoublyLinkList<TYPE>* list1, \
							DoublyLinkList<TYPE>* list2){
  if(list1->getHead() != NULL && list2->getHead() != NULL){
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current = list1->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }
   
    current = list2->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }
    if(this->head != NULL){
      delete this;
    }
    this->head=new_list->getHead();
    return this;
 
  }
  else if(list1->getHead() == NULL && list2->getHead() != NULL) {
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current = list2->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }
 
    if(this->head != NULL){
      delete this;
    }
    this->head=list2->getHead();
    return this;
 
  }
  else if(list2->getHead() == NULL && list1->getHead() != NULL){
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current = list1->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }

    
    if(this->head != NULL){
      delete this;
    }
    this->head=list1->getHead();
    return this;
 
  }
  else{
    // both are empty, now return empty list
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    if(this->head != NULL){
      delete this;
    }
    this->head=new_list->getHead();
    return this;
    
  }
}

//----------------------------------- Q2 (b)
template <class TYPE>
DoublyLinkList<TYPE>* DoublyLinkList<TYPE>::concatenateOrdered(DoublyLinkList<TYPE>* list1,	\
							       DoublyLinkList<TYPE>* list2){
  if(list1->getHead() != NULL && list2->getHead() != NULL){
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current1 = list1->getHead();
    Node<TYPE>*current2 = list2->getHead();
    if(current1 != NULL && current2 != NULL){
      while(current1 != NULL && current2 !=NULL){
	if(current1->data < current2->data){
	  new_list->insertAtEnd(current1->data);
	  current1 = current1->next;
	}
	else{
	  new_list->insertAtEnd(current2->data);
	  current2 = current2->next;
	}
      }
    }	     
    while(current1 != NULL){
      new_list->insertAtEnd(current1->data);
      current1 = current1->next;

    }
    while(current2 != NULL){
      new_list->insertAtEnd(current2->data);
      current2 = current2->next;
    }
    if(this->head != NULL){
      if(this->head != NULL){
	delete this;
      }
    }
    this->head=new_list->getHead();
    return this;
 
  }
  else if(list1->getHead() == NULL && list2->getHead() != NULL) {
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current = list2->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }
    if(this->head != NULL){
      delete this;
    }
    this->head=list2->getHead();
    return this;
 
  }
  else if(list2->getHead() == NULL && list1->getHead() != NULL){
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    Node<TYPE>*current = list1->getHead();
    while(current != NULL){
      new_list->insertAtEnd(current->data);
      current = current->next;
    }

    if(this->head != NULL){
      delete this;
    }
    this->head=list1->getHead();
    return this;
 
  }
  else{
    // both are empty, now return empty list
    DoublyLinkList<TYPE>* new_list = new DoublyLinkList<TYPE>();
    if(this->head != NULL){
      delete this;
    }
    this->head=new_list->getHead();
    return this;
  }
}
//----------------------------------- Q2 (c)
template <class TYPE>
DoublyLinkList<char>* DoublyLinkList<TYPE>::sumDoublyLinkList(const char* num1, const char* num2){
  // taking num1 and num2 as char
  // so that long numbers can be added
  // otherwise number could be added by + operator
  DoublyLinkList<char> list1;
  DoublyLinkList<char> list2;
  DoublyLinkList<char>* resultant = new DoublyLinkList<char>();
  int length1=0;
  int length2=0;
  while(num1[length1]) list1.insertAtEnd(num1[length1++]);
  while(num2[length2]) list2.insertAtEnd(num2[length2++]);
  int carry=0;
  Node<char>* tail1 = list1.getTail();
  Node<char>* tail2 = list2.getTail();
  while(tail1 !=NULL  && tail2 !=NULL){
    int unit;
    int sumOfTwoDigit = (tail1->data - '0')\
      + (tail2->data - '0') + carry;
    // subtracting 0 to make it int from char to perform arithmetic
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail1 = tail1->prev;
    tail2 = tail2->prev;
  }

  while(tail1 !=NULL){
    int unit;
    int sumOfTwoDigit = (tail1->data - '0') + carry;
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail1 = tail1->prev;

  }

  while(tail2 !=NULL ){
    int unit;
    int sumOfTwoDigit = (tail2->data - '0') + carry;
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail2 = tail2->prev;
  }
  if(carry !=0) resultant->insertAtStart(carry);
  if(this->head != NULL){
    delete this;
  }
  this->head=resultant->getHead();
  return this;
}
//----------------------------------- Q2 (c) overloading
template <class TYPE>
DoublyLinkList<TYPE>* DoublyLinkList<TYPE>::sumDoublyLinkList(TYPE num1, TYPE num2){
  // taking num1 and num2 as char
  // so that long numbers can be added
  // otherwise number could be added by + operator
  DoublyLinkList<TYPE> list1;
  DoublyLinkList<TYPE> list2;
  DoublyLinkList<TYPE>* resultant = new DoublyLinkList<TYPE>();
  int length1=0;
  int length2=0;
  while(num1 >0) {
    int unit= num1%10;
    list1.insertAtStart(unit);
    num1 = num1/10;
  }
  while(num2 >0) {
    int unit= num2%10;
    list2.insertAtStart(unit);
    num2 = num2/10;
  }

  int carry=0;
  Node<TYPE>* tail1 = list1.getTail();
  Node<TYPE>* tail2 = list2.getTail();
  while(tail1 !=NULL  && tail2 !=NULL){
    int unit;
    int sumOfTwoDigit = (tail1->data )\
      + (tail2->data ) + carry;
    // subtracting 0 to make it int from char to perform arithmetic
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail1 = tail1->prev;
    tail2 = tail2->prev;
  }

  while(tail1 !=NULL){
    int unit;
    int sumOfTwoDigit = (tail1->data ) + carry;
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail1 = tail1->prev;

  }

  while(tail2 !=NULL ){
    int unit;
    int sumOfTwoDigit = (tail2->data) + carry;
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
    tail2 = tail2->prev;
  }
  if(carry !=0) resultant->insertAtStart(carry);
  if(this->head != NULL){
    delete this;
  }
  this->head=resultant->getHead();
  return this;
}
