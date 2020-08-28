//fill array with random number
#include <iostream>
#include <stdlib.h>
#include <time.h>
//zaeem 19L-1196
using namespace std;
int main(){
	const int size=5;
	int myarray[size];
	srand(time(NULL));
	int rand_num;
	
	for(int i=0; i<5; i++){
	rand_num = rand()%21+5;
	myarray[i]=rand_num;
	}

	for(int i=0; i<5; i++)
		cout << myarray[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}