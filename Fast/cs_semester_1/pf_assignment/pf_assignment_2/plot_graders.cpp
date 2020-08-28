#include <iostream>
using namespace std;
int main(){
	int a=0,b=0,c=0,d=0,f=0;
	int students, marks;
	cout << "Marks entry point by Zaeem Yousaf\n";
	cout << "How many students: ";
	cin >> students;
	for(int counter=1; counter<= students; counter++){
		cout << "Enter  marks for student " << counter << ": ";
		cin >> marks;
		if(marks >=90 && marks <=100) a++;
		else if(marks >=75 && marks <= 89) b++;
		else if(marks >=60 && marks <= 74) c++;
		else if(marks >=50 && marks <= 59) d++;
		else if(marks < 50 && marks >=0) f++;
		else {cout << "invalid marks.\n"; counter--;}

	}
	//plotting
	cout << "A: ";
	for(int i=0; i< a; i++) cout << "*";
	cout << endl;

	cout << "B: ";
	for(int i=0; i< b; i++) cout << "*";
	cout << endl;
	cout << "C: ";
	for(int i=0; i< c; i++) cout << "*";
	cout << endl;
	cout << "D: ";
	for(int i=0; i< d; i++) cout << "*";
	cout << endl;
	
	cout << "F: ";
	for(int i=0; i< f; i++) cout << "*";
	cout << endl;
}