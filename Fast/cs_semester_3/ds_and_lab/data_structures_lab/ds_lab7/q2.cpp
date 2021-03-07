#include <iostream>
using namespace std;
bool Compare(char const* s1, char const* s2, int index);
int stringCompare(char const* s1, char const* s2);

int main() {

  char const* s1 = "Hate Fast";
  char const* s2 = "Kill FAST";
  int val= stringCompare(s1,s2);
  if (val == 0) {
    cout << "Strings are same.\n";
  }
  else if (val == 1) {
    cout << "String are not same.\n";
  }
	
  system("pause");
  return 0;
}

bool Compare(char const* s1, char const* s2, int index) {
  if (s1[index] != s2[index]) {
    return 1;
  }
  else if (s1[index] == '\0' && s2[index] == '\0') {
    return 0;
  }
  else {
    return Compare(s1, s2, index + 1);
  }
}

int stringCompare(char const* s1, char const* s2) {
  if (s1 == "" || s1 == "\0" || s2 == "" || s2 == "\0") {
    cout << "One of the given Strings is empty.\n";
    return -1;
  }
  else {
    int index = 0;
    return Compare(s1, s2, index);
  }
}
