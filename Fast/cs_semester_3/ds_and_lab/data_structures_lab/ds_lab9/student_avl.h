#include <iostream>
using namespace std;
template <class Type1, class Type2>
  void copy(Type1 *&var1, Type2 *&var2);

class Student{
 private:
  int roll_no;
  char* name;
  float cgpa;
 public:
Student(int,char*,float);
friend ostream& operator << (ostream &,Student &);
  int get_roll_no();
  char* get_name();
  float get_cgpa();
  ~Student();
};

struct StdNode{
  Student* data;
  int height;
  StdNode *lChild;
  StdNode *rChild;
  StdNode(){
    data=NULL;
    lChild = NULL;
    rChild = NULL;
  }
  ~StdNode(){
    if(data != NULL) delete data;
  }
};

class AVL{
private:
  StdNode* root;
  void inOrder(StdNode *root);
  void destroy_all_nodes(StdNode *root);
  StdNode* deleteNode(StdNode*, int rollNo);
  StdNode* smallest_roll_no(StdNode* node);
public:
  AVL();
  StdNode* get_root();
  void insertStudent(int _rollNumber, char* _name, float _cgpa);
  Student* search(int rollNumber);
  bool deleteStudent(int rollNumber);
  void inorderPrintStudentRollNumbers();
  ~AVL();
};

