#include <iostream>
using namespace std;
const int size=5;
float subtotal(float [],int);
void fill_array(float[],int);
void print_array(float [],int);
int main(){
	float array[size],ave;
	fill_array(array,size);
	ave=subtotal(array,size);
	print_array(array,size);
	cout << "The average is: " << ave <<endl;

	system("pause");
}
float subtotal(float array[],int size){
	int sum=0, ave;
	for(int i=0; i<size; i++){
	sum=sum+array[i];
	array[i]=sum;
}
	ave=sum/size;
	return ave;
}
void fill_array(float array[],int size){
	int value;
	for(int i=0; i< size; i++){
		cout << "enter " << i+1 << "th: ";
		cin >> value;
		array[i]=value;
	}
}
//-------------------
void print_array(float array[],int size){
	for(int i=0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}