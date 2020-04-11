#include <iostream>
using namespace std;
int main(){

	int s, marks;
	cout << "how many students: ";
	cin >> s;

	int i,j,k,l,m;
	i=j=k=l=m=0;
	for(int x=1; x<= s; x++){
		cout << "marks of student ";
		cin >> marks;
		if(marks >=90 && marks <=100) {
			i=i+1;
		}
		else if(marks >=75 && marks <= 89) {
			j=j+1;
		}
		else if(marks >=60 && marks <= 74) {
			k=k+1;
		}
		else if(marks >=50 && marks <= 59) {
			l=l+1;
		}
		else if(marks < 50 && marks >=0) {
			m=m+1;}

		else {
			cout << "marks not in range\n";
		}

	}

	cout << "A: ";
	for(int c=0; c< i; c++) {
		cout << "*";
	}
	cout << endl;

	cout << "B: ";
	for(int c=0; c< j; c++) {
		cout << "*";}

	cout << endl;

	cout << "C: ";
	for(int c=0; c< k; c++)
		{cout << "*";}
	cout << endl;
	cout << "D: ";
	for(int c=0; c< l; c++)
		{{cout << "*";}}
	cout << endl;

	cout << "F: ";
	for(int c=0; c< m; c++) {cout << "*";}
	cout << endl;
return 0;
}
