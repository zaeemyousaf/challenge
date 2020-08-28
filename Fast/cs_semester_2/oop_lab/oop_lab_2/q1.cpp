#include <iostream>
using namespace std;

int main(){
	int x, y;
	int *p, *q;
	x=2; y=8;
	p=&x; q=&y;

	cout << "address of x: " << p << "value of x is " << x << endl;
	cout << "the value of p: " << p << "value of *p: " << *p << endl;
	cout << "address of y " << q << "value of y is: " << y << endl;
	cout << "value of q: " << q << "value of *q is: " << *q << endl;
	cout << "address of p: " << &p << endl;
	cout << "address of q: " << &q << endl;
	
	
	system("pause");
	return 0;
}