#include <iostream>
int biggest(int , int , int );
using namespace std;
int main(){
cout << "enter three numbers to get the biggest: ";
int a,b,c;
cin >> a >> b >>c;
int big = biggest(a,b,c);
cout << "biggest integer is " << big << endl;
system("pause");
return 0;
}
int biggest(int a, int b, int c){
	if(a >b && a>c){return a;}
	else if(b > c && b> a){return b;}
	else{return c;};

}
