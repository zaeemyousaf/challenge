#include <iostream>
using namespace std;
// merge two array
// don't use nested loop
//----------------------
void my_merge(int A[],int B[],int C[],int m,int n){
	int A_index=0,B_index=0,C_index=0;
	for(int i=0; i< m && i < n; i++){
		if(A[A_index] < B[B_index]){
			C[C_index] = A[A_index];
			A_index++;
			C_index++;
		}
		else{
			C[C_index] = B[B_index];
			B_index++;
			C_index++;
		}
	}

		for(int i=A_index; i < m; i++){
			C[C_index] = A[A_index];
			C_index++;
			A_index++;
		}
		for(int i=B_index; i < n; i++){
			C[C_index] = B[B_index];
			C_index++;
			B_index++;
		}
	C[C_index]='\0';
}

//----------------------
int main(){
	//int array1[10],array2[12];
	int array1[10]={1,2,4,9,13,15,21,43,46,50};
	int array2[12]={3,5,6,7,8,10,11,12,14,16,17,'\0'};
	int array3[21];
	my_merge(array1,array2,array3,9,11);
	for (int i=0; i<20; i++) cout << array3[i] << " ";
}
