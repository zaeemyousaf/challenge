#include <iostream>
using namespace std;
int DisplayMenu(); //point 15 todo
class Node{
public:
private:
  int data;
  Node* next;
public:
  Node();
  Node(int data);
  void set_data(int data);
  int get_data();
  Node* get_next_ptr();
  void set_next_ptr(Node* new_ptr);
  void print();
  ~Node();
};
//-------------------------------------
  
class LinkedList{
private:
  Node* head;
public:
  LinkedList();
  LinkedList(const LinkedList& linked_list);
  void set_head(Node*ptr);
  Node * getStartPtr();
  Node * getLastPtr();
  void insertAtLast(int const element); // point 1
  void insertAthead(int const element); // point 2
  void insertAfter(Node &temp, int data); // Point
  Node search(int element) const; // Point 4
  void deleteNode(int data); // point 5
  void printLinkList() const; //point 6 
  void deletehead(); // point 7
  Node* cloneLinkList(); // point 8
  Node* ArrayToLinkList(int array[],int size); // point 9
  void sortLinkList(); // point 10 
  void reverseLinkList(); // point 11
  void insertInsortedLinkList(int data); // point 12 todo
  int sumtheElements();//point 13 todo
  void removeDublicateElement();//point 14 todo

  void deleteAtEnd();
  ~LinkedList();
};
//======================== end of prototype
 
Node::Node(){
  next = NULL;
}
//------------------------------------
Node::Node(int data){
  Node* first_node = new Node();
  first_node->data = data;
  first_node->next = NULL;
  
}
//-------------------------------------
void Node::set_data(int data){
  this->data=data;
}
//-------------------------------------
int Node::get_data(){
  return this->data;
}



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
Node* Node::get_next_ptr(){
  return this->next;
}
//-------------------------------------
void Node::set_next_ptr(Node* new_ptr){
    next = new_ptr;
}
//-------------------------------------
 
Node::~Node(){
}
//-------------------------------------
LinkedList::LinkedList(){
  // make one node
  head = NULL;
}

 
Node LinkedList::search(int data) const{
  Node* current_ptr = head;
  bool found=false;
  while(current_ptr != NULL && current_ptr->get_data() != data){
    current_ptr = current_ptr->get_next_ptr();
  }
  if(current_ptr->get_data() == data){
    return *current_ptr;
  }
}

 
void LinkedList::set_head(Node *ptr){
  head = ptr;
}
 
// void LinkedList::setLastPtr(Node *ptr){
//   last_ptr = ptr;
// }
//----------------------------------------
 
Node * LinkedList::getStartPtr(){
  return head;
}
//-----------------------------------------
 
// Node * LinkedList::getLastPtr(){
//   return last_ptr;
// }

//----------------------------------------
 
void LinkedList::insertAthead(int const element){
  Node *temp_node = new Node();
  temp_node->set_data(element);
  temp_node->set_next_ptr(head);
  head = temp_node;

  
}

//----------------------------------------
void LinkedList::insertAtLast(int const element){
  Node*temp_node = new Node();
  temp_node->set_data(element);
  temp_node->set_next_ptr(NULL);
  //d  last_ptr->next = temp_node;  
  //d  last_ptr = temp_node;
}

//----------------------------------------
void LinkedList::insertAfter(Node &temp, int data){
  Node* current_ptr = head;
  while(current_ptr != NULL && current_ptr->get_next_ptr() != &temp){
    current_ptr = current_ptr->get_next_ptr();
  }
  if(current_ptr != NULL){
    Node* toBeInserted = new Node();
    toBeInserted->set_data(data);
    toBeInserted->set_next_ptr(current_ptr->get_next_ptr());
    current_ptr->set_next_ptr(toBeInserted);
  }
}

//----------------------------------------
void LinkedList::deletehead(){
  if(head != NULL){
    Node* toBeDeleted = head;
    head = head->get_next_ptr();
    toBeDeleted->set_next_ptr(NULL);
    delete toBeDeleted;
    toBeDeleted = NULL;
  }
}

//----------------------------------------
void LinkedList::deleteAtEnd(){
  // 1: empty
  // 2: one node
  // 3: more than one node
  Node* current = head;
  Node* previous = current;
  while(current->get_next_ptr() != NULL){
    previous = current;
    current = current->get_next_ptr();
  }
  delete current;
  current = NULL;
  previous->set_next_ptr(NULL);
}
//----------------------------------------
Node* LinkedList::cloneLinkList(){
  LinkedList* new_link_list = new LinkedList();
  Node* current_ptr = head;
  while(current_ptr !=NULL){
    new_link_list->insertAthead(current_ptr->get_data());
    current_ptr = current_ptr->get_next_ptr();
  }
    
  return new_link_list->getStartPtr();
}
//----------------------------------------
Node* LinkedList::ArrayToLinkList(int array[], int size){
  LinkedList* new_link_list = new LinkedList();
  for(int i=0; i< size; i++){
    new_link_list->insertAthead(array[i]);
  }
}
//----------------------------------------
void LinkedList::sortLinkList(){
  Node* last_ptr = NULL;
  Node* current_ptr = head;
  Node* previous_ptr;
  Node* next_ptr;
  while(head != last_ptr){
    int current_data= current_ptr->get_data();
    previous_ptr = current_ptr;
    current_ptr = current_ptr->get_next_ptr();
    int next_data = current_ptr->get_data();
    next_ptr = current_ptr->get_next_ptr();
    bool ordered =false;
    if(current_data > next_data){
      // swap the nodes
      current_ptr->set_next_ptr(previous_ptr);
      previous_ptr->set_next_ptr(next_ptr);
      swaped = true;
    }
}


}
//----------------------------------------
void LinkedList::deleteNode(int v){
  if(head != NULL){
    // not empty
    // incase: element is in mid
    Node* current_ptr = head;
    bool deleted=false;
    while(current_ptr != NULL && deleted != false){
      //in case value to be deleted is mid or last element
      Node* previous_ptr;
      if(current_ptr->get_data() ==v && current_ptr != head){
	previous_ptr->set_next_ptr(current_ptr->get_next_ptr());
	delete current_ptr;
	current_ptr = previous_ptr;
      }
      else if(current_ptr->get_data() ==v && current_ptr == head){
	//in case value to be deleted is first element
	current_ptr = current_ptr->get_next_ptr();
	deletehead();
      }
      else{
	previous_ptr = current_ptr;
	current_ptr = current_ptr->get_next_ptr();
      }
    }
  }
}
//----------------------------------------
void LinkedList::printLinkList() const{
  Node* current_ptr = head;
  while(current_ptr != NULL){
    cout << current_ptr->get_data() << " ";
    current_ptr= current_ptr->get_next_ptr();
  }
  cout << endl;
}

//----------------------------------------
LinkedList::~LinkedList(){
  Node* current_ptr = head;
  Node* temp_ptr;
  while(current_ptr != NULL){
    temp_ptr = current_ptr->get_next_ptr();
    delete current_ptr;
    current_ptr= temp_ptr;
  }
}
//------------------------------------------------------
// void reverseLinkedList(LinkedList & linked_list){
//   if(linked_list.head != linked_list.last_ptr){
//     // more than one element and there is need to reverse the list
//     Node* begin_ptr = linked_list.head; // before this ptr, all are reversed
//     Node* end_ptr = linked_list.last_ptr; // after this ptr, all are reversed
//     Node* current_ptr =begin_ptr; // the runnning ptr
//     Node* previous_ptr = current_ptr;
//     while(begin_ptr != end_ptr){
//       while(current_ptr != end_ptr->next){

	
// 	previous_ptr = current_ptr;
// 	current_ptr = current_ptr->next;
//       }
//       // update begin_ptr and end_ptr
//       begin_ptr = begin_ptr->next;
//       end_ptr = previous_ptr;
//     }
//   }
  
// }
 
void LinkedList::reverseLinkList(){
  // count the elements
  // make a list of addresses of nodes in a linked list
  // then point nodes to address in reverse orders
  int total_nodes =0;
  Node* current_ptr = head;
  while(current_ptr != NULL) {
    current_ptr = current_ptr->get_next_ptr();
    total_nodes++;
  }

  // total nodes have been calculated
  Node**nodes = new Node*[total_nodes];
  //now copy addresses into array
  current_ptr = this->getStartPtr(); // reset current ptr
  for(int i=0; i< total_nodes; i++){
    nodes[i] = current_ptr;
    current_ptr = current_ptr->get_next_ptr();
  }
  for(int i=total_nodes-1; i > 0; i--){
    nodes[i]->set_next_ptr(nodes[i-1]);
  };
  nodes[0]->set_next_ptr(NULL);
  this->set_head(nodes[total_nodes-1]);
}
//------------------------------------------------------
int DisplayMenu(){
  int choice=0;
  do{
  cout << "press 1 to insertAtLast\n\
press 2 to insertAtFirst)\n\
press 3 to print\n\
press 0 to quit: ";
  cin >> choice;
  }
  while(choice <0 || choice >3);
  return choice;
}
int main(){
  
  LinkedList l1 = LinkedList();
  
}

