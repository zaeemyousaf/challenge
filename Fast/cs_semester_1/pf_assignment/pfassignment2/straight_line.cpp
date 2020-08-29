// adding documentation
#include <iostream> // basic header file
using namespace std; // using the namespaces from std
int main(){
  int a,b,x1,x2,y1,y2; // declaring variables
  cout << "enter x1 "; //prompting user
  cin >> x1; // getting user input
	cout << "Enter y1 ";
	cin >> y1;
	cout << "Enter x2 ";
	cin >> x2;
	cout << "Enter y2 ";
	cin >> y2;

	a=x2-x1; // for computing gradient sign
	b=y2-y1; 
	if (a <0){
	  a=-1*a;
            }
	if (b < 0) {
	    b=-1*b;
    }
	for(int i=0; i< b; i++){
		for(int j=0; j<(b-i); j++){
		  cout << " "; // printing only spaces to give 
		  // illusin of slanty line
		}
		cout << "*" << endl;
	}
	return 0;
}

