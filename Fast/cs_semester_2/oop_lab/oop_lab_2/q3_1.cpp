#include <iostream>
using namespace std;

void printer(int *x){
	cout << "squar is " << (*x)*(*x) << " cube is " << (*x)*(*x)*(*x) << " half is " << (*x)/2 << endl;

}
int main(){
	
	int x=2;
	printer(&x);

	
	system("pause");
	return 0;
}