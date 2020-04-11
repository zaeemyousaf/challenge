#include <iostream>
using namespace std;
int main(){
	int r;
	cout << "enter no of rows: ";
	cin >> r;

	for(int i=0; i< r; i++){

		for(int j=(r-1); j > (i+1) ; j--) {
cout << " ";}

for(int k=0; k < (i+1)*2-1; k++) {
				cout << "*";}
        cout << endl;
	}
	return 0;
}
