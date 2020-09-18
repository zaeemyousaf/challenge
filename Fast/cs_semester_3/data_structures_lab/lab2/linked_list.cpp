#include <iostream>
using namespace std;

class Node{
public:
  //private:
  int data;
  Node* next;
  //public:
  Node();
  void print();
  ~Node();
};
//-------------------------------------
class LinkedList{
private:
  Node* start_ptr;
  Node* last_ptr;
  
    
public:
  LinkedList();
  LinkedList(const LinkedList& linked_list);
  void insertAtStart(int const element);
  void insertAtEnd(int const element);
  bool search(int const& element) const;
  void insertAfter(int const v1, int const v2);
  void deleteFromStart();
  void deleteAtEnd();
  void deleteAllOccurrences(int v1);
  void print() const;
  ~LinkedList();
};


Node::Node(){
  next = NULL;
}
//-------------------------------------
void Node::print(){
  cout << "data: " << data << endl;
  if(next !=NULL){
    cout << "next: " << next << endl;
  }
  else{
    cout << "next: " << endl;
  }
}
//-------------------------------------
Node::~Node(){
}
//-------------------------------------
// Node
LinkedList::LinkedList(){
  // make one node
  start_ptr = NULL;
  last_ptr = NULL;
}

bool LinkedList::search(int const& v) const{
  Node* current_ptr = start_ptr;
  bool found=false;
  while(current_ptr != NULL && found !=true){
    if(current_ptr->data == v) found=true;
    current_ptr = current_ptr->next;
  }
  return found;
}

void LinkedList::insertAtStart(int const element){
  Node *temp_node = new Node();
  temp_node->data = element;
  temp_node->next = start_ptr;
  start_ptr = temp_node;
  if(last_ptr ==NULL) last_ptr = start_ptr;
  
}


void LinkedList::insertAtEnd(int const element){
  Node *temp_node = new Node();
  temp_node->data = element;
  temp_node->next = NULL;
  last_ptr->next = temp_node;  
  last_ptr = temp_node;
}

void LinkedList::insertAfter(int const v1, int const v2){
  Node* current_ptr = start_ptr;
  while(current_ptr != NULL && current_ptr->data != v2){
    current_ptr = current_ptr->next;
  }
  if(current_ptr != NULL){
    Node* toBeInserted = new Node();
    toBeInserted->data = v1;
    toBeInserted->next = current_ptr->next;
    current_ptr->next = toBeInserted;
  }
}
void LinkedList::deleteFromStart(){
  if(start_ptr != NULL){
    Node* toBeDeleted = start_ptr;
    start_ptr = start_ptr->next;
    delete toBeDeleted;
  }
}

void LinkedList::deleteAtEnd(){
  if(start_ptr == NULL){
    // do nothing
  }
  else if(start_ptr == last_ptr and start_ptr != NULL){
    // only one node
    delete start_ptr;
    start_ptr = NULL;
    last_ptr = NULL;
  }
  else{
    Node* toBeDeleted = start_ptr;
    Node* previous_node;
    while(toBeDeleted !=last_ptr){
      previous_node = toBeDeleted;
      toBeDeleted = toBeDeleted->next;
    }
    delete toBeDeleted;
    previous_node->next = NULL;
    last_ptr = previous_node;
  }
}

void LinkedList::deleteAllOccurrences(int v){
  if(start_ptr != NULL){
    // not empty
    // incase: element is in mid
    Node* current_ptr = start_ptr;
    while(current_ptr != NULL){
      //in case value to be deleted is mid or last element
      Node* previous_ptr;
      if(current_ptr->data ==v && current_ptr != start_ptr){
	previous_ptr->next = current_ptr->next;
	delete current_ptr;
	current_ptr = previous_ptr;
      }
      else if(current_ptr->data ==v && current_ptr == start_ptr){
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

void LinkedList::print() const{
  Node* current_ptr = start_ptr;
  while(current_ptr != NULL){
    cout << current_ptr->data << " ";
    current_ptr= current_ptr->next;
  }
  cout << endl;
}

LinkedList::~LinkedList(){
  Node* current_ptr = start_ptr;
  Node* temp_ptr;
  while(current_ptr != NULL){
    temp_ptr = current_ptr->next;
    delete current_ptr;
    current_ptr= temp_ptr;
  }
}

int main(){
  LinkedList l1 = LinkedList();
  l1.insertAtStart(2);
  l1.insertAtStart(6);
  l1.insertAtStart(7);
  l1.insertAtEnd(9);
  l1.insertAtStart(7);
  l1.insertAtStart(8);
  l1.insertAtStart(9);
  l1.deleteFromStart();
  l1.print();
  l1.search(2);
  l1.search(9);
  l1.search(10);
  l1.deleteAtEnd();
  l1.print();
  l1.insertAtEnd(100);
  l1.insertAfter(2,9);
  l1.print();
}
