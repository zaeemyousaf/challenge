//problem 1
#include <iostream>
using namespace std;
int main(){
float bmi, w, h;
cout << "Enter weight in pounds: ";
cin >> w;
cout << "Enter Height in inchs: ";
cin >> h;
bmi=w*703/(h*h);
if(bmi >=18.5){
	if(bmi <=25){cout << "Optimal.\n";}
	else{cout << "overweight.\n";}}
else{cout << "Underweight.\n";}
}//endif

