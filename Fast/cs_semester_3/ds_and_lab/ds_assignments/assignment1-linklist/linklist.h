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
class SinglyLinkList{
private:
  Node<TYPE>* head;
public:
  SinglyLinkList();
  SinglyLinkList(const SinglyLinkList& linked_list);
  void setHead(Node<TYPE>*ptr);
  Node<TYPE> * getHead();
  Node<TYPE> * getNthNode(int n); // returns nth node
  int getLength();
  void insertAtStart(TYPE const element);
  void insertAtEnd(TYPE const element);
  bool search(TYPE const& element) const;
  void insertAfter(TYPE const v1, TYPE const v2);
  void deleteFromStart();
  void deleteAtEnd();
  void deleteAllOccurrences(TYPE v1);
  void print() const;
  //------------------------------ miscellenous functions 
  void swapFirstWithLast();
  void swap(int a, int b);
  void rotateCounterClockWise(int k);

  SinglyLinkList<TYPE>* sumSinglyLinkList(TYPE num1, TYPE num2);
  SinglyLinkList<char>* sumSinglyLinkList(const char* num1, const char* num2);
  ~SinglyLinkList();
};
//-------------------------------------
template <typename TYPE>
void reverseSinglyLinkList(SinglyLinkList<TYPE> & linked_list);
//======================== end of prototype
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
//-------------------------------------
template <typename TYPE>
Node<TYPE>::~Node(){
}
//-------------------------------------

template <typename TYPE>
SinglyLinkList<TYPE>::SinglyLinkList(){
  // make one node
  head = NULL;

}

template <typename TYPE>
SinglyLinkList<TYPE>::SinglyLinkList(const SinglyLinkList& linked_list){
  // todo
}
template <typename TYPE>
bool SinglyLinkList<TYPE>::search(TYPE const& v) const{
  Node<TYPE>* current_ptr = head;
  bool found=false;
  while(current_ptr != NULL && found !=true){
    if(current_ptr->data == v) found=true;
    current_ptr = current_ptr->next;
  }
  return found;
}

template <typename TYPE>
void SinglyLinkList<TYPE>::setHead(Node<TYPE> *ptr){
  head = ptr;
}

//----------------------------------------
template <typename TYPE>
Node<TYPE> * SinglyLinkList<TYPE>::getHead(){
  return head;
}

//----------------------------------------
template <typename TYPE>
Node<TYPE> * SinglyLinkList<TYPE>::getNthNode(int n){
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
int SinglyLinkList<TYPE>::getLength(){
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
void SinglyLinkList<TYPE>::insertAtStart(TYPE const element){
  Node<TYPE> *temp_node = new Node<TYPE>();
  temp_node->data = element;
  temp_node->next = head;
  head = temp_node;
}

template <typename TYPE>
void SinglyLinkList<TYPE>::insertAtEnd(TYPE const element){
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
  }
  else{
    head = temp_node;
  }
}

template <typename TYPE>
void SinglyLinkList<TYPE>::insertAfter(TYPE const v1, TYPE const v2){
  Node<TYPE>* current_ptr = head;
  while(current_ptr != NULL && current_ptr->data != v2){
    current_ptr = current_ptr->next;
  }
  if(current_ptr != NULL){
    Node<TYPE>* toBeInserted = new Node<TYPE>();
    toBeInserted->data = v1;
    toBeInserted->next = current_ptr->next;
    current_ptr->next = toBeInserted;
  }
}

template <typename TYPE>
void SinglyLinkList<TYPE>::deleteFromStart(){
  if(head != NULL){
    Node<TYPE>* toBeDeleted = head;
    head = head->next;
    delete toBeDeleted;
  }
}

template <typename TYPE>
void SinglyLinkList<TYPE>::deleteAtEnd(){
  if(head == NULL){
    // do nothing
  }
  else if(head->next == NULL){
    // only one node
    delete head;
    head = NULL;
  }
  else{
    Node<TYPE>* toBeDeleted = head;
    Node<TYPE>* previous_node;
    while(toBeDeleted !=NULL){
      previous_node = toBeDeleted;
      toBeDeleted = toBeDeleted->next;
    }
    delete toBeDeleted;
    previous_node->next = NULL;
  }
}

template <typename TYPE>
void SinglyLinkList<TYPE>::deleteAllOccurrences(TYPE v){
  if(head != NULL){
    // not empty
    // incase: element is in mid
    Node<TYPE>* current_ptr = head;
    while(current_ptr != NULL){
      //in case value to be deleted is mid or last element
      Node<TYPE>* previous_ptr;
      if(current_ptr->data ==v && current_ptr != head){
	previous_ptr->next = current_ptr->next;
	delete current_ptr;
	current_ptr = previous_ptr;
      }
      else if(current_ptr->data ==v && current_ptr == head){
	//in case value to be deleted is first element
	current_ptr = current_ptr->next;
	deleteFromStart();
      }
      else{
	previous_ptr = current_ptr;
	current_ptr = current_ptr->next;
      }
    }
  }
}
template <typename TYPE>
void SinglyLinkList<TYPE>::print() const{
  Node<TYPE>* current_ptr = head;
  while(current_ptr != NULL){
    cout << current_ptr->data << " ";
    current_ptr= current_ptr->next;
  }
  cout << endl;
}

template <typename TYPE>
SinglyLinkList<TYPE>::~SinglyLinkList(){
  Node<TYPE>* current_ptr = head;
  Node<TYPE>* temp_ptr;
  while(current_ptr != NULL){
    temp_ptr = current_ptr->next;
    delete current_ptr;
    current_ptr= temp_ptr;
  }
}

template <typename TYPE>
void reverseSinglyLinkList(SinglyLinkList<TYPE> &linked_list){
  // count the elements
  // make a list of addresses of nodes in a linked list
  // then point nodes to address in reverse orders
  int total_nodes =0;
  Node<TYPE>* current_ptr = linked_list.getHead();
  while(current_ptr != NULL) {
    current_ptr = current_ptr->next;
    total_nodes++;
  }

  // total nodes have been calculated
  Node<TYPE>**nodes = new Node<TYPE>*[total_nodes];
  //now copy addresses into array
  current_ptr = linked_list.getHead(); // reset current ptr
  for(int i=0; i< total_nodes; i++){
    nodes[i] = current_ptr;
    current_ptr = current_ptr->next;
  }
  for(int i=total_nodes-1; i > 0; i--){
    nodes[i]->next = nodes[i-1];
  };
  nodes[0]->next = NULL;
  linked_list.setHead(nodes[total_nodes-1]);
}
