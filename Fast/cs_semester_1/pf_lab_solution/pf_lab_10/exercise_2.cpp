// Example program
#include <iostream>
using namespace std;
void encrypt(char []);
void decrypt(char []);
int main()
{
	char input[50];
	cin.get(input,50,'#');
	encrypt(input);
	cout << "Encrypted string" << endl;
	cout << input << endl;
	cout << "decrypted sequence: " << endl;
	decrypt(input);
	cout << input << endl;
	

	system("pause");
}
void encrypt(char array[]){
	int index=0;
	while(array[index] !='\0'){
	index++;
	}
	char c;
	cout << "max char " << index << endl;
	for(int i=0; i< index; i++){
		array[i]=array[i]+i;
	}
	array[index]='\0';


}
//------------------
void decrypt(char array[]){
	int index=0;
	while(array[index] !='\0'){
	index++;
	}
	char c;
	for(int i=0; i< index; i++){
		c=array[i]-i;
		array[i]=c;
	}
	array[index]='\0';
}