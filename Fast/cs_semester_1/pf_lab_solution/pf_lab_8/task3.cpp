#include <iostream>
using namespace std;
const int size=5;
void fill_array(int [],int);
void extreme_index(int [],int,int &,int&);
int main(){
	int myarray[size],sindex,lindex;
	fill_array(myarray,size);
	extreme_index(myarray,size,sindex,lindex);
	cout << "Largest Element Index: " << lindex << endl;
	cout << "Smallest Element Index: " << sindex <<endl;
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
void extreme_index(int array[],int size,int &si,int &li){
	int g=array[0],s=array[0];
	for(int i=0; i<size; i++){
		if(array[i] > g){g=array[i];li=i;}
		else if(array[i] < s){s=array[i];si=i;}

	}
}