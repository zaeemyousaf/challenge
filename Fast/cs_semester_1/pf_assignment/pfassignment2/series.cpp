#include <iostream>
using namespace std;
int main(){
	float sum,x,l;
	int t,f=1;
	cout << "enter x: ";
	cin >> x;
	cout << "enter terms: ";
	cin >> t;
	l=x;
	sum = 1;
	for(int i = 1; i <= t; i++ ){
		
		sum=sum+(l / f);
		l=l*x;
		f=f*(i+1);

	}
	cout << "result: " <<sum << endl;
}