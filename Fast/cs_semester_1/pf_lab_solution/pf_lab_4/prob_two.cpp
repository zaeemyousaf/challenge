#include <iostream>
using namespace std;
int main(){
float l,w;
cout << "enter the value for length: ";
cin >> l;
cout << "Enter the value of width: ";
cin >> w;
if(l==w){cout <<"your shape is square.\n";
cout << "The perimeter of this square is: "\
<< 2*(l+w) << "," << "and the area is: " << l*w << endl;
}
else{cout <<"your shape is rectangle.\n";
cout << "The perimeter of this rectangle is: "\
<< 2*(l+w) << "," << "and the area is: " << l*w << endl;
}

}//end main
