#include <iostream>
void bignumber(int , int , int , int &);
using namespace std;
int main(){
int a, b,c,largest;
cout << "enter 3 digits to print the max: ";
cin >> a >> b>>c;
bignumber(a,b,c,largest);
cout << "the largest is : " << largest << endl;

system("pause");
return 0;
}
void bignumber(int a, int b, int c, int & big){
	big = (a > b && a >c )? a : (b>c && b>a)? b : c;
}