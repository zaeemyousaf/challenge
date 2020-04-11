#include <iostream>
using namespace std;
int main(){
	bool binary=true;
	int digit, number;
	cout << "Zaeem Yousaf\n";
	cout << "Enter a number to test whether it is a binary no: ";
	cin >> number;
	number = (number < 0)? number*-1 : number;
	// also handles the negative number
	while (number > 9){
		// testing all digits except the most significant one
		digit = number % 10;
		number = number / 10;
		// upon decimal digt, break the loop
		// we know that it is no longer binary
		if (digit > 1) { binary=false; break;}
		// no else part

	}
	// testing most significant digit
	if(number > 1) binary=false; // no else part

	if(binary) cout << "it is binary.\n";
		else cout << "not binary.\n";

		return 0;
}