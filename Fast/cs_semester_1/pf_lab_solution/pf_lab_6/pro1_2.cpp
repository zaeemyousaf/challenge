#include <iostream>
bool iseven(int);
using namespace std;
int main(){
int n;
cout << "Enter a number to test for even: ";
cin >> n;
if(iseven(n)) cout << "it is even.\n";
else{cout << "not even.\n";}
system("pause");
return 0;
}
bool iseven(int x){
	if (x % 2==0){return 1;}
	else{return 0;}
}
