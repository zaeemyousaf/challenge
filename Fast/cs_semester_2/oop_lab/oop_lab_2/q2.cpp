#include <iostream>
using namespace std;

int main(){
	int x, y,sum;
	int *xPtr, *yPtr, *sumPtr;
	xPtr=&x; yPtr=&y; sumPtr=&sum;
	cout << "Enter two integers: "; 
	cin >> *xPtr >> *yPtr;
	sum=x+y;
	*sumPtr=sum;
	cout << *xPtr << "+" << *yPtr << "=" << *sumPtr << endl;


	
	system("pause");
	return 0;
}