#include <iostream>
using namespace std;
int main(){
	int a,b,x1,x2,y1,y2;
	cout << "enter x1 ";
	cin >> x1;
	cout << "Enter y1 ";
	cin >> y1;
	cout << "Enter x2 ";
	cin >> x2;
	cout << "Enter y2 ";
	cin >> y2;

	a=x2-x1;
	b=y2-y1;
	if (a <0){
            a=-1*a;
            }
	if (b < 0) {
	    b=-1*b;
    }
	for(int i=0; i< b; i++){
		for(int j=0; j<(b-i); j++){
			cout << " ";
		}
		cout << "*" << endl;
	}
	return 0;
}
