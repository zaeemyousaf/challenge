//utilize the power function builtin
#include <iostream>
#include <cmath>
//zaeem 19L-1196
void Power(double num, double exp, double &result){
		result = pow(num,exp);
}
using namespace std;
int main(){
	double result, n,p;
	cout << "enter: number power ";
	cin >> n >> p;
	Power(n,p,result);
	cout <<"ans:" <<  result << endl;
	system("pause");
}