#include <iostream>
using namespace std;
const int size=5;
int getNthIndex(int [], int,int, int);
void fill_array(int [],int);

int main(){
	int myarray[size],value,n;
	fill_array(myarray,size);
	cout <<"occurance of what? ";
	cin >> value; 
	cout << "how many occurances: ";
	cin >> n;
	int index=getNthIndex(myarray,size,value,n);
	cout << "total occurances are : " << index << endl;

	system("pause");
}

int getNthIndex(int array[],int size,int value, int n){
	int occ=0;
	for(int i=0; i<size; i++){
		if(array[i]==value){
			occ++;
			if(occ==n){return i;}
		}
	}
	return -1;
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