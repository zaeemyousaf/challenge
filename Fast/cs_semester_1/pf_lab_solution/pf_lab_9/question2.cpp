#include <iostream>
using namespace std;
const int size=5;
bool is_unimodel(int [],int);
void fill_array(int[],int);
void print_array(int [],int);

int main(){
	int array[size],ave;
	fill_array(array,size);
	int is_uni=is_unimodel(array,size);
	if(is_uni) cout << "it is in unimodel: " << endl;
	else{cout << "it is not in unimodel: " << endl;}
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
//--------------------
bool is_unimodel(int array[],int size){
	int max=array[0],index=0;
	while(max < array[index+1]){
		max=array[index+1];
		index=index+1;
		}
	//cout << "index is : "<< index <<endl;
	//descending order check
	bool inorder=1;
	for(int i=index+1; i<size; i++){
		if(max <= array[i]) {
			//cout << "passing " <<endl;
			inorder=0; break;}
	}

	if(inorder) return 1;
	else{return 0;}
