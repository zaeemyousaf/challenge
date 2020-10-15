#include <iostream>
#include <fstream>
using namespace std;
int com_str(const char *str1, const char *str2);

template <class T>
class Node{
public:
  Node();
  T data;
  Node<T>* next;
};

template<class T>
class Stack {
public:
  Stack() ;
  ~Stack();
  bool IsEmpty();
  bool push( T &val);
  bool pop();
  T Top();
  void print();
private:
  Node<T> * top;
};

template <class T>
Node<T>::Node(){
  next=NULL;
}

template <class T>
Stack<T>::Stack(){
  top = NULL;
}

template <class T>
Stack<T>::~Stack(){
  while(top) pop();
}
template <class T>
bool Stack<T>::IsEmpty(){
  if(top != NULL) return false;
  return true;
}

template <class T>
bool Stack<T>::push(T &element){
  Node<T>* temp_node = new Node<T>();
  temp_node->data=element;
  temp_node->next=top;
  top = temp_node;
  return true;
}

template <class T>
bool Stack<T>::pop(){
  if(top != NULL){
    Node<T>* toBeDeleted = top;
    top = top->next;
    toBeDeleted->next=NULL;
    delete toBeDeleted;
    toBeDeleted = NULL;
    return true;
  }
  else{return false;}
}

template <class T>
T Stack<T>::Top(){
  return top->data;
}

template <class T>
void Stack<T>::print(){
  Node<T>* temp_node = top;
  while(temp_node != NULL){
    cout << temp_node->data << "\n";
    temp_node = temp_node->next;
  }
}

template <class T>
class HtmlData{
private:
  Stack<char*> tags;
  int line_number;
  void parse(char line[]);
  bool match(char* str1,char* str2);
public:
  HtmlData(const char* fileName);
  void print_errors();
  ~HtmlData();
};
//===============================
template <class T>
HtmlData<T>::HtmlData(const char* fileName){
  line_number =0;
  // open file for reading
  fstream fin(fileName);
  char line[200];
  while(!fin.eof()){
    fin.getline(line,200,'\n');
    parse(line);
  }
}

template <class T>
void HtmlData<T>::parse(char line[]){
  line_number++; // inc when it is invocated
  //cout << line;
  // it will push opening tags
  // if closing encountered
  // it will match the pop
  // if mismatch then
  // line is printed
  // else ignore printing
  int column=0;
  while(line[column] != '\0'){
    //   //bool tag_detected=false;
    char* tag = new char[10];
    int tag_index=0;
    if(line[column] == '<'){
      // start recording the tag
      tag[tag_index++] = line[column];
      int tag_column = column; // position of error on the line
      column++;
      while(line[column] == ' ' && line[column] != '\0') column++; // skip spaces
      while(line[column] != '>' && line[column] != '\0' && line[column] != ' '){
	tag[tag_index++]=line[column];
	column++;
      }

      // handle properties
      int single_quotes = 0;
      int double_quotes = 0;
      int single_quote_column =column; // track of pos of '
      int double_quote_column =column;// track of position of "
      while(line[column] != '\0' && line[column] != '>'){
	// still in opening tag and reading quotes
	if(line[column]=='"') {
	  double_quotes++;
	  double_quote_column =column; // update pos
	}
	if(line[column]=='\'') {
	  single_quotes++;
	  single_quote_column =column; // update pos
	}
	column++;
      }
      if(single_quotes %2 !=0) {
	cout << "[SYNTAX-ERROR on line " << line_number << ": single quote does not match]\n";
	cout << line << endl;
	for(int i=0; i< single_quote_column; i++) cout << " ";
	cout << "^\n";
      }
      if(double_quotes %2 !=0){
	cout << "[SYNTAX-ERROR on line " << line_number << ": double quote does not match]\n";
	cout << line << endl;
	for(int i=0; i< double_quote_column; i++) cout << " ";
	cout << "^\n";
      }

      if(line[column] == '>'){
	tag[tag_index++] = '>';
	tag[tag_index] = '\0';
	tag_column = column;
      }
      //cout << tag_index << "------------------";
      //cout << tag << " ";
      if(tag[1] == '/'){
	// closing tag, pop and match
	//cout<<tag << " " << "------------------- close found\n";
	if(match(tag,tags.Top())){
	  tags.pop();
	  //cout << "matching occured\n";
	}
	else{
	  cout << "[SYNTAX-ERROR on line " << line_number << ": tag mismatch]\n";
	  cout << line << endl;
	  for(int i=0; i< tag_column; i++) cout << " ";
	  cout << "^\n";
	  tags.pop();
	}
      }
      else{
	//opening tag, push
	//cout << "pushing: " << tag << endl;
	tag_column = column;
	tags.push(tag);
	     
      }
    }
    column++;
  }

}

template <class T>
bool HtmlData<T>::match(char *close_tag, char* open_tag){
  //cout << "comparing : " << close_tag << " " << open_tag << endl;
  if(close_tag && open_tag){
    if(close_tag[0] == open_tag[0]){
      // < == <
      int index=1;
      while(close_tag[index]!='\0' && open_tag[index] != '\0'){
	if(close_tag[index+1] != open_tag[index]) return false;
	index++;
      }
      if(close_tag[index+1] == open_tag[index]) return true;
    }
  }
  else{return false;}
}

template <class T>
HtmlData<T>::~HtmlData(){
  // stack will become empty
  // when printing and poping
}

int main(){
  HtmlData<char> d1("simple.html");
   // stack is implimented inside the HtmlData class
  // system("pause"); // uncomment for visual user 
  return 0;
}

int com_str(const char *str1, const char *str2){
  int index=0;
  if(str1 ==0 && str2 !=0) return -1;
  if(str2 ==0 && str1 !=0) return 1;
  while(str1[index] && str2[index]){
    if(str1[index] > str2[index]) return 1;
    else if (str1[index] < str2[index]) return -1;

    index++;
  }
  if(str1[index] > str2[index]) return 1;
  else if (str1[index] < str2[index]) return -1;
  else{return 0;}  
}
