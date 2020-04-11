#include<iostream>
using namespace std;
const int size=5;
void fill_array(int [],int);
void largerThanNumbger(int [], int );

int main(){

	int myarray[size],number;
	fill_array(myarray,size);
	cout << "Enter a number: ";
	cin >> number;
	largerThanNumbger(myarray,number);
system("pause");
}
void fill_array(int array[],int size){
	int value;
	for(int i=0; i< size; i++){
		cout << "enter " << i+1 << "th: ";
		cin >> value;
		array[i]=value;
	}
}
//--------------------- largerThanNumber
void largerThanNumbger(int array[], int number){
	int counter=0;
	for(int i=0; i < size; i++){
		if(array[i] > number){
		counter++;
		}
		
	}
	cout << "greaters are : " << counter << endl;
}