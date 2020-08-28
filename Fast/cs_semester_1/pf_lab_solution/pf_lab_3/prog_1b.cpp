//------------------------- problem 1 B
#include <iostream>
using namespace std;
int main(){
float number1, number2, Sum, Product, Subtract, Divide, Modulus;
cout << "enter two number one by one \n";
cin >> number1;
cin >> number2;
Sum=number1 + number2 ;
Product=number1*number2;
Subtract=number1-number2;
Divide = number1 / number2;
Modulus= (int )number1 % (int )number2 ;
//------------- printint to screen
cout << "sum is :" << Sum << endl;
cout << "product is: " << Product <<endl;
cout << "substraction is: " << Subtract << endl;
cout << "Division is: " << Divide << endl;
cout << "Remainder is : " << Modulus << endl;

return 0;

}
