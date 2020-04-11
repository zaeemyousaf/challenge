#include <iostream>
using namespace std;
int main(){
	int r;
	cout << "enter no of rows";
	cin >> r;

	for(int i=1; i<= r; i++){
		for(int j=0; j < r -i; j++)
        {
            cout << " ";
        }
		for(int k=1; k <= i; k++)
        {cout << "*";
		if(k==i){cout << endl;}
        }
	}
}
