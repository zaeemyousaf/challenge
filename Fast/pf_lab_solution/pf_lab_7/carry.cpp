#include <iostream>
using namespace std;
//zaeem 19L-1196
int Carrys( int num1, int num2){
	int carries=0,d1,d2;
	int smaller, greater;
	smaller = (num1 < num2)? num1: num2;
	greater = (num1 > num2)? num1: num2;
	int carry=0;
	while(smaller !=0){
			d1=smaller %10;
			d2=greater %10;
			smaller=smaller /10;
			greater=greater /10;
			if (d1+d2+carry > 9){
					carries++;
					carry=(d1+d2+carry)%10;
			}

	}
	return carries;
}

int main(){
	int num1,num2;	
	cout << "Enter two numbers: ";
	cin >> num1 >> num2;
	cout << Carrys(num1,num2) << endl;
	system("pause");
}