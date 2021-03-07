

#include <iostream>
#include "student_avl.h"
using namespace std;
template <class Type1, class Type2>
void copy(Type1 *&var1, Type2 *&var2){
  // copy var2 into var1
  if(var2 == 0) {
    var1=0;
  }
  else{
    int length=0;
    while(var2[length++]);
    var1 = new char[length];
    for(int i=0; i<=length; i++) var1[i]=var2[i];
  }
}

Student::Student(int _roll_no, char* _name, float _cgpa){
  roll_no = _roll_no;
  copy(name,_name);
  cgpa = _cgpa;
}

char* Student::get_name(){
  return name;
}
float Student::get_cgpa(){
  return cgpa;
}

ostream& operator <<(ostream &out,Student &obj){
  out << "Student detail ...\n";
  out << "Roll_no: " << obj.roll_no << " Name: " << obj.name << " cgpa: " << obj.cgpa << endl;
  return out;
}
int Student::get_roll_no(){
  return roll_no;
}

// Student::set_roll_no(int rollNo){
//   roll_no = rollNo;
// }
Student::~Student(){
  if(name != NULL){
    delete []name;
    name = NULL;
  }
}

AVL::AVL(){
  root = NULL;
}

StdNode* AVL::get_root(){
  return root;
}

void AVL::insertStudent(int _rollNumber, char* _name, float _cgpa){
  Student *s = new Student(_rollNumber,_name,_cgpa);
  StdNode *node= new StdNode();
  node->data = s;
  node->height = 0;
  node->lChild = NULL;
  node->rChild = NULL;
  
  if(root == NULL){
    root = node;
  }
  else{
    StdNode *node_index = root;
    StdNode *prev_node = root;
    while(node_index != NULL){
      
      int node_roll_no = node_index->data->get_roll_no();
      if(_rollNumber > node_roll_no){
	// follow right
	//cout << "following right \n";
	node_index->height--;
	prev_node = node_index;
	node_index = node_index->rChild;
      }
      else{
	// follow left
	//cout << "following left\n";
	node_index->height++;
	prev_node = node_index;
	node_index = node_index->lChild;
      }
    }
    //insert node_index here
    int node_roll_no = prev_node->data->get_roll_no();
    //cout << "node rollNo: " << node_roll_no << endl;
    if(_rollNumber > node_roll_no){
      prev_node->rChild = node;
      //prev_node->height--;
      //cout << "added node on right...\n";
    }
    else{
      //cout << "added node on left...\n";
      prev_node->lChild = node;
      //prev_node->height++;
    }
    //---------------- node has been inserted
    // now is the time to balance
    
  }
}
Student* AVL::search(int _rollNumber){
  StdNode *node_index = root;
  while(node_index != NULL){
    int node_roll_no = node_index->data->get_roll_no();
    if(_rollNumber == node_roll_no){
      return node_index->data;
    }
    else if(_rollNumber > node_roll_no){
      // follow right
      node_index = node_index->rChild;
    }
    else{
      // follow left
      node_index = node_index->lChild;
    }
  }
  return NULL;
}

void AVL::inOrder(StdNode *root_ptr){
  if(root_ptr == NULL){
    return;
  }
  else{
    //cout << "before printing left node " << endl;
    inOrder(root_ptr->lChild);
    cout << root_ptr->data->get_roll_no() << " ";
    //cout << "balance factor: " << root_ptr->height << endl;
    inOrder(root_ptr->rChild);
    //cout <<  "going to traverse right " << root_ptr << endl;
  }

}

bool AVL::deleteStudent(int rollNumber){
  Student *s = search(rollNumber);
  if(root && s){
    cout << "deleting student...";
  return true;
  }
  return false;
}
void AVL::inorderPrintStudentRollNumbers(){
  inOrder(root);
}

void AVL::destroy_all_nodes(StdNode *root){
  if(root == NULL){
    return;
  }
  destroy_all_nodes(root->lChild);
  destroy_all_nodes(root->rChild);
  //cout << "deleting " << root->data->get_roll_no() << endl;
  delete root;
}


AVL::~AVL(){
  // just a wrapper function to be called itself
  if(root != NULL){
    destroy_all_nodes(root);
  }
  cout << "All nodes destroyed successully";
  
}
