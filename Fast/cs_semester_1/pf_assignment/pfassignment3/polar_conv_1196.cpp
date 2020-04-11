#include <iostream>
#include <cmath>
//19L-1196
//polar to cartisian and vice versa
using namespace std;

void polar_to_cart(float , float, float &, float&);
void cart_to_polar(float, float, float &, float&);


int main()
{
    float x,y,r,theta;
    int choice;
    cout << "Enter your choice: \n1: cartision to polar\n2: polar to cartisian\n3: exit.";
    cin >> choice;
    while(choice != 3){
        switch(choice){
case 1:
    cout << "enter x coordinate: ";
    cin >> x;
    cout << "enter y coordinate: ";
    cin >> y;
    cart_to_polar(x,y,r,theta);
    cout << "r is " << r << endl;
    cout << "theta is " << theta << endl;

    break;
case 2:
    cout << "enter r: ";
    cin >> r;
    cout << "enter theta: ";
    cin >> theta;
    polar_to_cart(r,theta,x,y);
    cout << "x is " << x << endl;
    cout << "y is " << y << endl;

    break;
    }
    cout <<"===============================\n";
    cout << "Enter your choice: \n1: cartision to polar\n2: polar to cartisian\n3: exit.";
    cin >> choice;
    }

    return 0;
}
void polar_to_cart(float r, float theta, float &x,float &y){
    x=r*cos(theta);
    y=r*sin(theta);
}
void cart_to_polar(float x,float y,float &r, float &theta){
    r= sqrt(x*x +y*y);
    theta= atan(y/x);
}
