//------------------------------ Problem 2
#include <iostream>
using namespace std;
int main(){
int x,y, temp;
cout << "Enter value of of x: ";
cin >> x;
cout << "Enter value of of y: ";
cin >> y;

//swapping 
temp=x;
x=y;
y=temp;
cout << "value of x is : " << x << endl;
cout << "value of y is : " << y;
return 0;
}
