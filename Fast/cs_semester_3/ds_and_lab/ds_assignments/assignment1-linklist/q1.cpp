#include <iostream>
#include "linklist.h"
using namespace std;

int main(){
    SinglyLinkList <int> s1 = SinglyLinkList<int>();
  // <int> means: data type of 'node->data' is int
  s1.insertAtEnd(7);
  s1.insertAtEnd(9);
  s1.insertAtEnd(9);
  s1.insertAtEnd(10);
  s1.insertAtEnd(20);
  cout << "list1 is ...\n";
  s1.print();
  cout << "first node is swapped with last\n";
  s1.swapFirstWithLast();
  cout << "-------------------\n";
  s1.print();
  cout << " swap(2,4) \n";
  s1.swap(2,4);
  s1.print();
  cout << "-------------------\n";
  cout << " rotation counterclockwise k=3\n";
  s1.rotateCounterClockWise(3);
  s1.print();
  cout << "-------------------\n";
  cout << "123+999 by linked list\n";
  s1.sumSinglyLinkList(30,30);
  s1.print();
  cout << "-------------------\n";
  SinglyLinkList<char> s2;
  cout << "sum of two char arrays by linked list\n";
  s2.sumSinglyLinkList("","");
  s2.print();
  // system("pause") // for visual user
  return 0;
  
}

template <class TYPE>
void SinglyLinkList<TYPE>::swapFirstWithLast(){

    if(this->getHead() != NULL){
    if(this->getHead()->next != NULL){
      // more than one node
      Node<TYPE>* current = this->getHead();
      Node<TYPE>* prev = NULL;
      while(current->next != NULL){
	prev = current;
	current = current->next;
      }
      if(prev != this->getHead()){
	current->next = this->getHead()->next;
	this->getHead()->next = NULL;
	prev->next = this->getHead();
	this->setHead(current);
      }
      else{
	// there are only two elements
	current->next = this->getHead();
	this->getHead()->next = NULL;
	this->setHead(current);
      }
      
    }
  }
}

//--------------------
template <class TYPE>
void SinglyLinkList<TYPE>::swap(int first, int second){
  if(second < first){
    int temp=first;
    first = second;
    second = first;
  }
  int count=0;
  Node<TYPE>* current= this->getHead();
  while(current != NULL) {
    current = current->next;
    count++;
  }
  if(count >= first && \
     count >= second && \
     first*second >1 && \
     first != second){
    // now swaping is possible
    if(first ==1 and second==count) this->swapFirstWithLast();
    else{
      // no need to modify the head
      Node<TYPE>* a = this->getNthNode(first);// node a
      Node<TYPE>* pa = this->getNthNode(first-1); // previous of a
      Node<TYPE>* b = this->getNthNode(second); // node b
      Node<TYPE>* pb = this->getNthNode(second-1);// previous of node b
      Node<TYPE>* temp;
      temp = a->next;
      a->next = b->next;
      if(b != temp){
	b->next = temp;
      }
      else{
	b->next = a;
      }
      if(pa != NULL) pa->next = b;
      if(pb != a){
	pb->next = a;
      }

      if(first == 1){
	this->setHead(b); // modify head only of first node is tempered
      }
    }

  }
  else{
    // do nothing
    cout << "such nodes do not exist\n";
  }
}

//----------------------------------
template <class TYPE>
void SinglyLinkList<TYPE>::rotateCounterClockWise(int k){
  if(k < 0){
    cout << "k should be positive\n";
  }
  else
    {
      // effective rotations will be k%length
      int length = this->getLength();
      for(int i=0; i < k % length; i++){
	// % in case of very large number of rotation
	TYPE element = this->getNthNode(1)->data;
	this->deleteFromStart();
	this->insertAtEnd(element);
      }
    }
      
}

//------------------------------------
template <class TYPE>
SinglyLinkList<char>* SinglyLinkList<TYPE>::sumSinglyLinkList(const char* num1, const char* num2){
  // taking num1 and num2 as char
  // so that long numbers can be added
  // otherwise number could be added by + operator
  SinglyLinkList<TYPE> list1;
  SinglyLinkList<TYPE> list2;
  //if(this->head != NULL) delete this;
  //SinglyLinkList<TYPE>* resultant = new SinglyLinkList<TYPE>();
  SinglyLinkList<TYPE>* resultant = new SinglyLinkList<TYPE>();
  int length1=0;
  int length2=0;
  while(num1[length1]) list1.insertAtEnd(num1[length1++]);
  while(num2[length2]) list2.insertAtEnd(num2[length2++]);
  int carry=0;
  while(length1 > 0 && length2 > 0){
    int unit;
    int sumOfTwoDigit = (list1.getNthNode(length1--)->data - '0')\
      + (list2.getNthNode(length2--)->data - '0') + carry;
    // subtracting 0 to make it int from char to perform arithmetic
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }

  while(length1 > 0 ){
    int unit;
    int sumOfTwoDigit = (list1.getNthNode(length1--)->data - '0') + carry;
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }

  while(length2 > 0 ){
    int unit;
    int sumOfTwoDigit = (list2.getNthNode(length2--)->data - '0') + carry;
    unit = (sumOfTwoDigit % 10)+'0'; // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }
  if(carry !=0) resultant->insertAtStart(carry);
  this->head = resultant->getHead();
  return this;
}

template <class TYPE>
SinglyLinkList<TYPE>* SinglyLinkList<TYPE>::sumSinglyLinkList(TYPE num1, TYPE num2){

  SinglyLinkList<TYPE> list1;
  SinglyLinkList<TYPE> list2;
  SinglyLinkList<TYPE>* resultant = new SinglyLinkList<TYPE>();

  int length1=0;
  int length2=0;
  while(num1 >0) {
    int unit= num1%10;
    list1.insertAtStart(unit);
    num1 = num1/10;
    length1++;
  }
  while(num2 >0) {
    int unit= num2%10;
    list2.insertAtStart(unit);
    num2 = num2/10;
    length2++;
  }
  int carry=0;
  while(length1 > 0 && length2 > 0){
    int unit;
    int sumOfTwoDigit = (list1.getNthNode(length1--)->data)\
      + (list2.getNthNode(length2--)->data) + carry;
    // subtracting 0 to make it int from char to perform arithmetic
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }

  while(length1 > 0 ){
    int unit;
    int sumOfTwoDigit = (list1.getNthNode(length1--)->data) + carry;
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }

  while(length2 > 0 ){
    int unit;
    int sumOfTwoDigit = (list2.getNthNode(length2--)->data) + carry;
    unit = (sumOfTwoDigit % 10); // char value of digit
    resultant->insertAtStart(unit);
    carry = sumOfTwoDigit/10;
  }
  if(carry !=0) resultant->insertAtStart(carry);
  this->head = resultant->getHead();
  return this;
}
