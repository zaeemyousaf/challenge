#include <iostream>
using namespace std;

void init(int *ptr1, int *ptr2, int *ptr3){
	*ptr1=3; *ptr2=3; *ptr3=3;
}

int median(int *ptr1,int *ptr2, int *ptr3){
	int temp=0;
	if(*ptr1 > *ptr2) {temp=*ptr1; *ptr1=*ptr2; *ptr2=temp;}
	if(*ptr2 > *ptr3) {temp=*ptr2; *ptr2=*ptr3; *ptr3=temp;}
	if(*ptr1 > *ptr2) {temp=*ptr1; *ptr1=*ptr2; *ptr2=temp;}
	return *ptr2;
}
int main(){
	
	int x=-50,y=50,z=0;
	cout << median(&x,&y,&z);
	
	system("pause");
	return 0;
}