#include <iostream>
using namespace std;
float pi=3.142; // global var
float r;
//-----------------------------------function prototypes
float Area(float );
float Area(float , float );
double Area(double , double );
//------------------------------------
int main(){
int choice;
cout << "#####Welcome to Area Calculator#####\n";
cout << "1) Press 1 to calculate area of a circle. \n";
cout << "2) press 2 to calculate area of a triangle.\n";
cout << "3) Press 3 to calculate the area of cylinder.\n";
cout << "enter you choice: ";
cin >> choice;
if (choice == 1){
	cout << "Enter the radius of circle. ";
	cin >> r;
	cout << "the area of circle is :" << Area(r) << endl;
	}
else if(choice == 2){
	float base, height;
	cout << "enter base and height: ";
	cin >> base >> height;
	cout << "the area of triangle is : " << Area(base,height) << endl;}
else if(choice ==3){
	double r;
	cout << "enter the radius: ";
	cin >> r;
	double height;
	cout << "enter the height of cylinder: ";
	cin >> height;
	cout << "the Area of cylinder is : " << Area(height,r)\
	<< endl;
		
	}
system("pause");
return 0;
}

float Area(float r){
	return (pi*r*r);
}
//-------------------
float Area(float base, float height){
	return (.5*base*height);
}
//-------------------
double Area(double height, double rad){
	return(2*pi*rad*height+2*pi*rad*rad);
}