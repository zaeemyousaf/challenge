#include <iostream>
using namespace std;
void swap(int *x,int *y){
	*x=(*x)*(*y);
	*y=*x/(*y);
	*x=*x/(*y);

}
int main(){
	
	int x=10,y=20;
	cout << x << " " << y << endl;
	swap(&x,&y);
	cout << x << " " << y << endl;
	system("pause");
	return 0;
}