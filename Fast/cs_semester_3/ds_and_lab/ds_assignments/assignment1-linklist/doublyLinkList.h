#include <iostream>
using namespace std;
template <class TYPE>
class Node{
public:
  TYPE data;
  Node* next;
  Node* prev;

  Node();
  Node(TYPE data);
  ~Node();
};

template <class TYPE> 
Node<TYPE>::Node(){
  next=NULL;
  prev=NULL;
}

template <class TYPE> 
Node<TYPE>::Node(TYPE data){
  this->data = data;
  this->next=NULL;
  this->prev = NULL;
}

template <class TYPE> 
Node<TYPE>::~Node(){
}
//======================== DoublyLinkList

template <class TYPE>
class DoublyLinkList{
private:
  Node<TYPE>* head;
  Node<TYPE>* tail;
public:
  DoublyLinkList();
  DoublyLinkList(TYPE const element);
  void setHead(Node<TYPE>* ptr);
  void setTail(Node<TYPE>* ptr);
  Node<TYPE>* getHead();
  Node<TYPE>* getTail();
  void insertAtStart(TYPE const element);
  void insertAtEnd(TYPE const element);
  void DeleteAtStart();
  void DeleteAtEnd();
  void print();
  void reverse();
  void removeDuplicates();
  bool insertBefore(TYPE const v1, TYPE const v2 );
  //--------------------------------
  DoublyLinkList<TYPE>*  concatenate(DoublyLinkList<TYPE>* list1,\
				   DoublyLinkList<TYPE>* list2);
DoublyLinkList<TYPE>* concatenateOrdered(DoublyLinkList<TYPE>* list1,	\
					 DoublyLinkList<TYPE>* list2);

  DoublyLinkList<TYPE>* sumDoublyLinkList(TYPE num1, TYPE num2);
  DoublyLinkList<char>* sumDoublyLinkList(const char* num1, const char* num2);
  ~DoublyLinkList();
};

template <class TYPE>
DoublyLinkList<TYPE>::DoublyLinkList(){
  head = NULL;
  tail = NULL;
}

template <class TYPE>
DoublyLinkList<TYPE>::DoublyLinkList(TYPE const element){
  insertAtStart(element);
}

template <class TYPE>
void DoublyLinkList<TYPE>::setHead(Node<TYPE>* ptr){
  head = ptr;
}
template <class TYPE>
void DoublyLinkList<TYPE>::setTail(Node<TYPE>* ptr){
  tail = ptr;
}
template <class TYPE>
Node<TYPE>* DoublyLinkList<TYPE>::getHead(){
  return head;
}
template <class TYPE>
Node<TYPE>* DoublyLinkList<TYPE>::getTail(){
  return tail;
}

template <class TYPE>
void DoublyLinkList<TYPE>::insertAtStart(TYPE const element){
  Node<TYPE>* temp = new Node<TYPE>(element);
  temp->next = head;
  temp->prev = NULL;
  if(head != NULL){
  head->prev = temp;
  }
  head = temp;	// update head
  if(head->next == NULL) tail = head; // in case of zero or one element
}

template <class TYPE>
void DoublyLinkList<TYPE>::insertAtEnd(TYPE element){
  Node<TYPE>* temp = new Node<TYPE>(element);
  if(head != NULL){
    temp->next = NULL;
    tail->next = temp;
    temp->prev = tail;
    tail = temp; // update tail
  }
  else{
    head = temp;
    tail = temp;
  }
}

template <class TYPE>
void DoublyLinkList<TYPE>::DeleteAtStart(){
  if(head != NULL && head != tail){
    // more than one nodes
    head = head->next;
    head->prev->next=NULL;
    delete head->prev;
    head->prev = NULL;
  }
  else if(head != NULL && head == tail){
    // one node
    tail = NULL;
    delete head;
    head =NULL;
  }
}

template <class TYPE>
void DoublyLinkList<TYPE>::DeleteAtEnd(){
  if(head != NULL && head != tail){
    // more than one nodes
    tail = tail->prev;
    tail->next->prev = NULL;
    delete tail->next;
    tail->next = NULL;
  }
  else if(head != NULL && head == tail){
    // one node
    tail = NULL;
    delete head;
    head = NULL;
  }
}

template <class TYPE>
void DoublyLinkList<TYPE>::print(){
  Node<TYPE>* current = head;
  while(current!= NULL){
    cout <<	current->data << " ";
    current = current->next;
  }
  cout << endl;
}

template <class TYPE>
void DoublyLinkList<TYPE>::reverse(){
  Node<TYPE>* current = tail;
  Node<TYPE>* previous_ptr;
  while(current != NULL ){
    previous_ptr = current->prev;
    current->prev = current->next;
    current->next = previous_ptr;
    current = current->next;
  }
  // now swapping head and tail
  Node<TYPE>* temp = head;
  head = tail;
  tail = temp;
}

template <class TYPE>
void DoublyLinkList<TYPE>::removeDuplicates(){
  Node<TYPE>* start = head;
  if(head != NULL ){
    // more than one node
    while(start->next != NULL){
      Node<TYPE>* current = start->next;
      while( current->next != NULL){
	if(current->data == start->data){
	  // duplicate found
	  current->prev->next = current->next;
	  current->next->prev = current->prev;
	  current->next = NULL;
	  current->prev = NULL;
	  delete current;
	  current = NULL;
	}
	current = current->next;
      }
      start = start->next;
    }
  }
}

template <class TYPE>
bool DoublyLinkList<TYPE>::insertBefore(TYPE const v1, TYPE const v2 ){
  if(head != NULL){
    Node<TYPE>* current = head;
    bool inserted = false;
    while(current->next != NULL && inserted == false){
      if(current->data == v2){
	// found
	Node<TYPE>* temp = new Node<TYPE>(v1);
	temp->next = current;
	temp->prev = current->prev;
	current->prev = temp;
	inserted = true;
	// if inserted at start then update head
	if(current == head ) head = temp;
	// if inserted at end then update tail
	else if(current ==tail) tail = temp;
      }
      current = current->next;
    }
  }
  else{return false;}
}

template <class TYPE>
DoublyLinkList<TYPE>::~DoublyLinkList(){
  Node<TYPE>* current = head;
  if(current != NULL){
    if(current != tail){
      // more than one elements
      current = current->next;
      delete current->prev;
      
    }
    else{
      delete head;
      head=NULL;
      tail =NULL;
    }
  }
}
