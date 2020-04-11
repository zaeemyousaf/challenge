#include <iostream>
using namespace std;
void factorial(int , int &);
int main(){
int n, f;
cout << "enter a number to computer its factorial: ";
cin >> n;
factorial(n,f);
cout << "the factorial of " << n << " is " << f << endl;
system("pause");
return 0;
}
void factorial(int x, int & fact){
	fact=1;
	for(int i=1; i<=x; i++){
	fact=fact*i;
	}
}