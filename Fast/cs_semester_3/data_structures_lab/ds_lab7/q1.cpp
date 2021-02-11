#include <iostream>
using namespace std;
bool Palindromecheck(std::string& s, int start, int end) {
  if (start > end) {
    return 0;
  }
  else if (s[start] != s[end]) {
    return 1;
  }
  else {
    return Palindromecheck(s, start + 1, end - 1);
  }
}

bool Palindrome(std::string s) {
  if (s == "" || s == "\0") {
    cout << "string is empty.\n";
    return -1;
  }
  else {
    int size = s.length();
    return Palindromecheck(s, 0, size-1);
  }

}

int main() {

  int val=Palindrome("1221");
  if (val == 0) {
    cout << "String is Palindrome.\n";
  }
  else if (val == 1) {
    cout << "String isnot a Palindrome.\n";
  }
	
  //system("pause"); uncomment for visual studio
  return 0;
}
