// tags:
// tokenizer, words, sentence, split
#include <iostream>

using namespace std;

int n_words_in_str(char str[],char word_to_search[]){
    int index=0;
    int word_index=0;
    int n_words=0;
char word[20]; // reasonable length;
  int wi=0; // word index
  do{
    if(str[index] != ' ' && str[index] != '\0'){
      // copy
      word[wi++]=str[index];
    }
    else{
      // word completed
      word[wi]='\0';
      //cout << word << endl;
      bool same=true;
      int i;
      for(i=0; i< wi && word_to_search[i] != '\0'; i++){
	if(word[i] != word_to_search[i]) {same=false;break;}
      }
      if(word[i] != word_to_search[i] ) same=false;
      if (same) n_words++;

      for(int i=0; i< 20; i++) word[i]='\0'; // flushing buffer
      wi=0;
    }
  }while(str[index++] != '\0');
  return n_words;
}


void GetInput(){
    cout << "enter a string  ";
    char str[100];
    cin.getline(str,100,'.');
    int index=0;
    char word[20];
    //int word_index=0;
    char unique_words[100];
    int ui=0; // index of unique words
   
    int wi=0; // word index
  do{
    if(str[index] != ' ' && str[index] != '\0'){
      // copy
      word[wi++]=str[index];
    }
    else{
      // word completed
      word[wi]='\0';
      int words=0;
	    words= n_words_in_str(unique_words,word);
            if(words==0){
	      for(int i=0; i< wi; i++) unique_words[ui++]= word[i];
	      unique_words[ui++]= ' ';
	      unique_words[ui]='\0';
	      //cout << unique_words << "*************";
	      int occurrences = n_words_in_str(str,word);
	      if(index != 0){
		// to avoid last value printed twice
	      cout << word << ": " << occurrences << endl;
	      }
	    }
	    //else{cout << "already searched...";}


      for(int i=0; i< 20; i++) word[i]='\0'; // flushing buffer
      wi=0;
    }
  }while(str[index++] != '\0');	  
  }
//-------------------------
/*
void separate_words(const char str[]){
  int index=0;
  char word[20]; // reasonable length;
  int wi=0; // word index
  do{
    if(str[index] != ' ' && str[index] != '\0'){
      // copy
      word[wi++]=str[index];
    }
    else{
      // word completed
      word[wi]='\0';
      cout << word << endl;
      for(int i=0; i< 20; i++) word[i]='\0'; // flushing buffer
      wi=0;
    }
  }while(str[index++] != '\0');
}
*/
int main()
{
  /*
  separate_words("hi");
separate_words("");
separate_words("hi how");
separate_words(" hi are");
separate_words(" hi      ");
  */

 
  char words[] = "this is a list and list";
  char w1[]="this";
  char w2[]="a";
  char w3[]="list";
  char w4[]="not";
  char w5[]="is"; 
 cout << "should be 1 " << n_words_in_str(words,w1) << endl;
  cout << "should be 1 " << n_words_in_str(words,w2) << endl;
  cout << "should be 2 " << n_words_in_str(words,w3) << endl;
  cout << "should be 0 " << n_words_in_str(words,w4) << endl;
 cout << "should be 1 " << n_words_in_str(words,w5) << endl;

 
//    char array[]="this is long string this";
//    char word[]="this";
//    int count = word_in_str(array,word);
//    cout << count ;
 GetInput();

}
