#include <iostream>
using namespace std;
int calculate(int x, int y, int a, int b, int num);
int pre_calculate(int x, int y, int a, int b, int num);
int total_bills(int x, int y, int a, int b, int num);

int main() {

  total_bills(0,0,5,3,27);

  system("pause");
  return 0;
}

int calculate(int x, int y, int a, int b, int num) {
  if (((a * x) + (b * y)) > num) {
    return -1;
  }else if (((((num - (b * y)) / a) % a) == 0) && (((a * x) + (b * y)) == num)) {
    x = (num - (b * y)) / a;
    cout << "The total number of " << a << " & " << b << " bills in " << num << " is " << x << " & " << y << " .\n";
    return 0;
  }
  else {
    y++;
    calculate(x, y, a, b, num);
  }
}

int pre_calculate(int x, int y, int a, int b, int num) {
  if (((a * x) + (b * y)) > num) {
    return -1;
  }
  else if (((((num - (a * x)) / b) % b) == 0) && (((a * x) + (b * y)) == num)) {
    y = (num - (a * x)) / b;
    cout << "The total number of " << a << " & " << b << " bills in " << num << " is " << x << " & " << y << " .\n";
    return 0;
  }
  else {
    x++;
    pre_calculate(x, y, a, b, num);
  }
}


int total_bills(int x, int y, int a, int b, int num) {
  if (pre_calculate(x, y, a, b, num) != -1) {
    return 0;
  }
  else if (calculate(x, y, a, b, num) != -1) {
    return 0;
  }
  else {
    cout << "Calculation not possible.\n";
  }
}
