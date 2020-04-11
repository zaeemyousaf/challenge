#include <iostream>
using namespace std;

int find_subarray(const int *A, const int *B, int asize, int bsize){
	int A_i=0, B_i;
	int counter=0;
	bool match;
	while(A_i < asize){
		B_i=0;
		if(A[A_i]==B[B_i]){
			match=true;
			// start matching the rest one
			for( ; B_i < bsize;B_i++){
				if(A[A_i] != B[B_i]) {match=false; break;}
				A_i++;
			}
			if(match) counter++;
		}

		A_i++;
	}
	return counter;
}



int main(){
	int A[5]={1,2,9,1,2};
	int B[2]={1,2};
	cout << find_subarray(A,B,5,2);
	system("pause");
	return 0;
}