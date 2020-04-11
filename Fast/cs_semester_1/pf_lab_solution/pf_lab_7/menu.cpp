#include <iostream>
#include <stdlib.h>
#include <time.h>
//zaeem: 19L-1196
//--------------- function prototypes
int show_menu();
int Search(int [],int);
bool Delete(int [], int &, int );
bool Insert(int [], int, int &, int);
void Print(int [],int &);

using namespace std;
int main(){
	const int capacity=10;
	int array[capacity];
	int choice, index=0, num,key;
	
		bool rvalue;
	choice= show_menu();
	while(choice !=5){
		switch(choice){
		case 1:
			cout <<"==============================\n";
			cout <<"enter a number to insert: ";
			cin >> num;
			Insert(array,capacity,index,num);
			break;
		case 2:
			cout <<"==============================\n";
			cout << "enter a key to delete: ";
			cin >> key;
			Delete(array,index,key);
			break;
		case 3:
			cout <<"==============================\n";
			// search
			cout << "what to search: ";
			cin >> key;
			Search(array,key);
			break;
		case 4: 
			cout <<"==============================\n";
			Print(array,index);
			break;
		}
		choice=show_menu();
	}
	system("pause");
	return 0;
}

// Defining functions here
int Search(int arr[],int key){
	for(int i=0; i< 10; i++){
		if(key==arr[i]) {
			cout <<"found at 0 based index: " << i <<endl; 
			return i;}
	}
	cout << key << " not found in the array.\n" << endl;
	return -1; // if program come here, means not found
	
}
bool Delete(int arr[], int &index, int key){
	int location= Search(arr,key);
	if(location == -1) {
		cout << "Specified element not found in Array!" <<endl;
		return -1; // not found
	}
	else{
	int newArray[10]; //copy
	int counter=0;
	for(int i=0; i<index; i++){
		if(i !=location){
			newArray[counter]=arr[i];
			counter++;
		}
	for(int i=0; i<counter; i++){
		arr[i]=newArray[i];
	}
	}
	index=index-1; // after deleting, index decreases
	return true;}
}
bool Insert(int arr[], int capacity, int & index, int element){
	if(index < capacity){
		arr[index] = element;
		index++;
		return true;
	}
	else{
		cout << "no room to insertion.\n";
		return false; // in case of error
	}
}

//---------------------------
void Print(int arr[],int & index){
	cout << "Elements of an array: ";
	for(int i=0; i < index; i++){
	cout << arr[i] << " ";
	}
	cout << endl;
}

int show_menu(){
	// to avoid long line, I used folowing backslash

	cout << "Enter your choice\n\
1: Insert\n\
2: Delete\n\
3: Search\n\
4: Print\n\
5: Exit: ";
	int c;  //choice
cin >> c;
return c;
}