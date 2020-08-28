// Example program
#include <iostream>
using namespace std;
void reverseWords(char []);
int main()
{
	char words[50];
	cout << "Enter string followed by # to reverse word by word \n";
	cin.get(words,50,'#');
	reverseWords(words);
	cout << words;
	//system("pause");
	return 0;
}
void reverseWords(char array[]){


	int index=0;
	char c;
	int last_index=index;
	while(array[index] !='\0'){
		if(array[index] == ' '){
			int start=last_index,stop=index-1;
			while(start < stop){
				c=array[start];
				array[start]=array[stop];
				array[stop]=c;
			start++;
			stop--;
			}//end for
			last_index=index+1;
		}//end if
		
		index++;
	}//end while
	array[index]='\0';
}
