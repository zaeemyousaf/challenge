#include <iostream>
using namespace std;

template <typename TYPE> 
class Node{
public:
  TYPE data;
  Node* next;

  Node();
  Node(TYPE data);
  void print();
  ~Node();
};
//-------------------------------------
template <typename TYPE> 
class LinkList{
private:
  Node<TYPE>* head;
public:
  LinkList();
  LinkList(const LinkList& linked_list);
  void setHead(Node<TYPE>*ptr);
  Node<TYPE> * getHead();
  Node<TYPE> * getNthNode(int n); // returns nth node
  int getLength();
  bool isEqual(LinkList<TYPE>* l1);
  void insertAtStart(TYPE const element);
  Node<TYPE>* insertAtTail(TYPE element, Node<TYPE>* head_ptr);
  bool search(TYPE const& element) const;
  void insertAfter(TYPE const v1, TYPE const v2);
  void deleteFromStart();
  void deleteAtEnd();

  void print(Node<TYPE>* head_ptr) const;

  ~LinkList();
};
//-------------------------------------
template <typename TYPE>
void reverseLinkList(LinkList<TYPE> & linked_list);
//======================== end of prototype
template <typename TYPE>
Node<TYPE>::Node(){
  next = NULL;
}
//-------------------------------------
template <typename TYPE>
Node<TYPE>::Node(TYPE data){
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
LinkList<TYPE>::LinkList(){
  // make one node
  head = NULL;

}

template <typename TYPE>
LinkList<TYPE>::LinkList(const LinkList& linked_list){
  // todo
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
template<typename TYPE>
bool LinkList<TYPE>::isEqual(LinkList<TYPE>* l1){
  
}
template <typename TYPE>
void LinkList<TYPE>::insertAtStart(TYPE const element){
  Node<TYPE> *temp_node = new Node<TYPE>();
  temp_node->data = element;
  temp_node->next = head;
  head = temp_node;
}

template <typename TYPE>
Node<TYPE>* LinkList<TYPE>::insertAtTail(TYPE element,Node<TYPE>* head_ptr){
{ 

  if (head_ptr == NULL){
    Node<TYPE>* temp = new Node<TYPE>(element);
    if(head == NULL) head = temp;
    return temp;
  }

  else {
      head_ptr->next = insertAtTail(element,head_ptr->next); 
    return head_ptr; 
  }
 }
}

template <typename TYPE>
void LinkList<TYPE>::insertAfter(TYPE const v1, TYPE const v2){
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
void LinkList<TYPE>::deleteFromStart(){
  if(head != NULL){
    Node<TYPE>* toBeDeleted = head;
    head = head->next;
    delete toBeDeleted;
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
void LinkList<TYPE>::print(Node<TYPE>* head_ptr) const{
  if(head_ptr == NULL) return;
  cout << head_ptr->data << " ";
  print(head_ptr->next);
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

template <typename TYPE>
void reverseLinkList(LinkList<TYPE> &linked_list){
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
