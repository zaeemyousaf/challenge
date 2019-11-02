#include <iostream>
using namespace std;
int main(){
	int x,y;
	cout << "enter x: ";
	cin >> x;
	cout << "enter y: ";
	cin >> y;
	for(int i=x; i<=y; i++){
		cout << "--------Table of " << i << "--------\n";
		for(int j=1; j<=10; j++){
		cout << i << " x " <<j << "  : " << i*j << endl;
		}
			
	}
	system("pause");
	return 0;
}