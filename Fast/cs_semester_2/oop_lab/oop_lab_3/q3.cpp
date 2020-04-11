#include <iostream>
using namespace std;

void extended_array(int *&arr,int &size);
void fill_array(int *&arr,int size);

int main(){
	int size;
	cout << "enter input size: ";
	cin >> size;
	int *A= new int [size];

	fill_array(A,size);
	extended_array(A,size);

	for(int i=0; i< size; i++) cout << A[i] << " ";
	system("pause");
	return 0;
}
//--------------------
void extended_array(int *&arr,int &size){
	// making new array
	int new_size=0,t_i=0;
	for(int i=0; i< size; i=i+2) {new_size=new_size+arr[i];}
	//cout << "new size is " << new_size;
	int *temp= new int [new_size];
	for(int i=0; i<size; i=i+2){
		for(int j=0; j< arr[i]; j++) *(temp+t_i++)=*(arr+i); 
	}
	delete []arr;
	arr=temp;
	size=new_size;
}
//---------------------
void fill_array(int *&arr,int size){
	for(int i=0; i< size; i++) cin >> *(arr+i);
}