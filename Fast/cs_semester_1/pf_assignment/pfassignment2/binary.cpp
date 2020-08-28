#include <iostream>
using namespace std;
int main(){
	int bin=true;
	int d, n;
	cout << "enter an integer for binary test: ";
	cin >> n;
	while (n !=0){
		d = n % 10;
		n = n / 10;
		if (d > 1) {
			bin=false;
		}

	}

	if(bin==true) {cout << "it is binary.";}
		else cout << "it is not binary.";

		return 0;
}
