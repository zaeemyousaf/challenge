// problem 4:
#include <iostream>
using namespace std;
int main(){
float h_wages=9.25;
float hours, extra_hours,extra_sal,sal;
cout << "how many hours worked in past week? :";
cin >> hours;
extra_hours = (hours > 40)? hours-40 : 0;
extra_sal=extra_hours*1.5*9.25;
sal=extra_sal+hours*h_wages;
cout << "total salary is : " << sal << endl;
}//end main