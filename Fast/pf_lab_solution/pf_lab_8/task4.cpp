#include <iostream>
using namespace std;
const int size=5;
void fill_array(int [],int);
void printElementsAtEvenIndex(int [],int);
void printEvenElements(int [],int);
void reversePrint(int [],int);
int main(){
	int myarray[size];
	fill_array(myarray,size);
	cout << "values at even index: \n";
	printElementsAtEvenIndex(myarray,size);
	cout <<"Even values: ---------\n";
	printEvenElements(myarray,size);
	cout << "printing in reverse order\n";
	reversePrint(myarray,size);
	system("pause");
}


//----------------------- fill_array
void fill_array(int array[],int size){
	int value;
	for(int i=0; i< size; i++){
		cout << "enter " << i+1 << "th: ";
		cin >> value;
		array[i]=value;
	}
}
//-----------------
void printElementsAtEvenIndex(int array[],int size){
	for(int i=0; i<size; i++){
		if(i %2==0){cout << array[i] << " ";}
	}
			cout << endl;
}
//-------------------
void printEvenElements(int array[],int size){
	for(int i=0; i<size; i++){
		if((array[i] %2)== 0){cout << array[i] << " ";}
	}
			cout << endl;
}
//--------------------- reverse print
void reversePrint(int array[],int size){
	for(int i=size-1; i>=0; i--){
		cout << array[i] <<" ";
	}
	cout << endl;
}