#include <iostream>
using namespace std;

void reverse(int arr[],int size){
	for (int i=size-2; i >=0; i--){
		cout << arr[i] << " ";

	}

}

void grow_double(int *&arr,int &size){
	int *temp = new int[2*size];
	// copy contents
	for (int i=0; i< size; i++){
		temp[i]=arr[i];
	}
	delete []arr;

	arr=temp;
	size=2*size;

	

}

int main(){
	int size=5, num=0;
	int *A=new int[size];
	int counter=0;

	while(num != -1){
		if(counter == size) grow_double(A,size);
		cin >> num;
		//*(A+counter)=num;
		A[counter]=num;
		counter ++;
	}
	size=counter;
	reverse(A,size);
	system("pause");
	return 0;
}