#include <iostream>
using namespace std;
const int size=5;
void selection_sort(int [],int);
int min_search(int [],int,int);
void fill_array(int[],int);
void print_array(int [],int);
int bin_search(int [],int,int);

int main(){
	int array[size],ave;
	fill_array(array,size);
	selection_sort(array,size);
	cout << "sorted array: "; 
	print_array(array,size);
	int key;
	cout << "what do you want to search from the array: ";
	cin >> key;
	int index=bin_search(array,size,key);
	if(index !=-1) cout << "found at " << index << endl;
	else{cout << "Not found in the array " << endl;}
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
//-------------------
void print_array(int array[],int size){
	for(int i=0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}
void selection_sort(int array[],int size){
	for(int i=0; i<size; i++){
		int ind=min_search(array,size,i);
		int temp;
		if(array[i] > array[ind]){
		temp=array[i];
		array[i]=array[ind];
		array[ind]=temp;

	}
	}
}
int min_search(int array[],int size,int start){
	int i=start,min,index=start;
	min=array[i];
	i=i+1;
	for(; i< size; i++){
		if(array[i] < min){
			min=array[i];
			index=i;
		}
	}
	return index;
}
//----------------
int bin_search(int array[],int size,int key){
	int s=0, e=size, m;
	while(s < e){
		m=(e+s)/2;
		if(array[m] == key) return m;
		else if(array[m] > key) e=m-1;
		else {s=m+1;}
	
	}
	return -1;
}