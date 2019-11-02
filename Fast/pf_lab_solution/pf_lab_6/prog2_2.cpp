#include <iostream>
using namespace std;
int main(){
int f,s,temp;
cout << "enter the 1st number: ";
cin >> f;
cout << "enter the second number: ";
cin >> s;
temp=s;
s=f;
f=temp;
cout << "After swapping the 1st number is :" << f << endl;
cout << "After swapping the 2nd number is :" << s << endl;
system("pause");
return 0;
}