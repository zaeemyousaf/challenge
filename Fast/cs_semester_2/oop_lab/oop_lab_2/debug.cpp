#include <iostream>
using namespace std;

void switchPtr (int *p,int *q)
{
	int *temp = p;
	p = q;
	q = temp;
}
//---------------
int acceptPtr(int *p, int *q)
{
	*p = *q + 5;
	*q = *q + 10;
	p = q;
	*p = 5 + *q;
	*q = *p + 1;

	return *p+1;
}
//--------------
int dontComplicate(int *p,int *q,int &a,int &b)
{
	a = a+1;
	b = b+2;

	q = p;
	*p = 3;
	*q = 5;

	a = a+4;
	b = b+5;
	return *p + *q;
} 
//------------
int notVerySimple(int *ptr1,int *ptr2,int &a,int &b)
{
	*ptr1 = 1;
	*ptr2 = 5;
	a = 4;
	b = 3;
	return a+b;
}



int main(){
	
	int x=1, y=2, z=0;
	
	int *ptr1=&x;
	int *ptr2=&y;
	 
	switchPtr(ptr1,ptr2);
		
	z=acceptPtr(ptr1,ptr2);
		x = 0;	y = 1;
		
	z=dontComplicate(ptr2,ptr1,y,x);
		
	z=notVerySimple(ptr1,ptr2,x,y);
		
	
	system("pause");
	return 0;
}