#include <iostream>
using namespace std;
int main(){
	int s2lr=3,factor; // space2lineRatio 
	//2 spaces : 1 line
	float m, b,x,y;
	factor=5; // change and see the effect
	// it controls the the number of points

	cout << "zaeem Yousaf. line eq y = mx+b \n";
	cout << "Enter m: ";
	cin >> m;
	cout << "Enter b: ";
	cin >> b;

	x=factor*s2lr;
	y=factor*m;
	//----------------
	cout << "\n^ y-axis\n";
	int line=0,space;
	while(line<= y ){
		cout << "|";
		for(space=1; (space < x) && (x >0); space++) {
			cout << " ";
		}
				cout << "*" << endl;
			for(int i=0; (i < m); (i++,y--)) cout << "|" << endl;
	
			x=x-s2lr; // skipping some lines to creat gradient alusion
			line++;
	}
	for(int i=0; i< b; i++) cout << endl; // for b
	cout << "-----------------------------> x-axis\n";
 

	return 0;
}