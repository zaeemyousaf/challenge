#include <iostream>
using namespace std;
int substr(char arr[],char str[]){
	int si=0, ai=0;
	bool found;
	while(arr[ai] != '\0'){
		//cout << "-------";
		if(str[si] == arr[ai] && arr[ai-1]== ' '){
			found=true;
			int index=ai;
			while(str[si] != '\0'){
				if(str[si] != arr[ai]){found=false; ai++;break;}
				else{si++;}
				ai++;
			}
			if(found) return index;
		//else{ai++;}
		}
	ai++;
	}
	return -1;
}
void removeDuplicateWords(char arr[]){
	char duplicate[500]="\0";
	int di=0;//dupliate index
	int ai=0; // array index
	char word[20];
	int wi=0; // word index

	while(arr[ai] != '\0'){
		//------------------------pick a word
		if(arr[ai] != ' ' && arr[ai] != '.') {word[wi]=arr[ai]; wi++;}
		else{
			//word has completed
			word[wi]= '\0';
		//------------------------ word pick end
			wi=0;
			// search word in duplicate array
			// if not there, then insert
			int exist=substr(duplicate,word);
			if(exist == -1){
				//insert word into duplicate array
				while(word[wi] != '\0'){
					duplicate[di]=word[wi];
					di++;
					wi++;
				}
				// insert space after
				duplicate[di++]=' ';
			}
			wi=0;
		}
		ai++;
	}
	duplicate[di]='\0';
	//copy into previous array
	for(int i=0; i<=di; i++) arr[i]=duplicate[i];
}
int main(){
	char str[50]="this is is is is str.";
	removeDuplicateWords(str);
	cout << str;
}