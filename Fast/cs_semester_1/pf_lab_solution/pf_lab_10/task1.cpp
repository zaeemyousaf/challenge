// Example program
#include <iostream>
using namespace std;
bool isPalindrome(char []);

int main()
{
    char input[10];
    cout << "Enter a string to test palindrome. ";
    cin >> input;
    bool r= isPalindrome(input);
    if(r==1){
     cout << "it is palindrome." <<endl;;
    }
    else{cout << "not palindrome." <<endl;;}

	system("pause");
}


bool isPalindrome(char input[]){
    int index=0;
    bool p=true;
    while(input[index] != '\0'){
     index++;   
    }
    
    for(int i=0; i<index; i++){
        if(input[i] != input[index-i-1]) {
            p=false;
            break;
            };
    }
    return p;
}
