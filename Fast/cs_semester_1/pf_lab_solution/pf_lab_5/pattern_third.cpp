#include <iostream>
using namespace std;
int main(){
	int nlines;
	cout << "no of lines: ";
	cin >> nlines;
	for(int i=0; i< nlines; i++){
		for(int j=1; j<=i+1; j++){
			cout << "*";
		}
		cout << endl;
	}
	cout << "" << endl;

	for(int i=0; i< nlines; i++){
		for(int j=nlines-i; j>=1; j--){
			cout << "*";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}