//problem 3
#include <iostream>
using namespace std;
int main(){
int first,second,third;
cout << "enter space separted three numbers: ";
cin >> first >> second >> third;
if (first > second && second > third){
	cout << "in order\n";}
else if (third > second && second > first){
	cout << "in order\n";
}
else{cout << "not in order\n";}
	
}
