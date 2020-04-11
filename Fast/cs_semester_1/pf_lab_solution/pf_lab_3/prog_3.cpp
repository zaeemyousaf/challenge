//------------------------------- Problem 3
#include <iostream>
#include <string>
using namespace std;
int main(){
string fName, lName, degree, rollNo;
cout << "Enter your first Name: ";
getline(cin, fName);
cout << "Enter your Last Name: "; 
getline(cin, lName);
cout << "Enter your Roll No: ";
getline(cin, rollNo);
cout << "Enter your Degree: " ;
getline(cin, degree);

//printing to screen
cout << "Name:        "<< fName << lName <<endl;
cout << "RollNo:"<<rollNo << endl;
cout << "Program: " << degree;


return 0;
}
