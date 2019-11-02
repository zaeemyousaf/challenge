#include<iostream>
using namespace std;
int main(){
float sum=0.0,term;
int denom=1,sign=1;
for(int i=0; i<100; i++){
term=4.0/denom;
term=term*sign;
//cout << term << endl;
sum=sum+term;
sign=sign*-1;
denom+=2;
}

cout << "pi value with 100 iterration: " << sum << endl;

sum=0.0,term;
denom=1,sign=1;
for(int i=0; i<200; i++){
term=4.0/denom;
term=term*sign;
//cout << term << endl;
sum=sum+term;
sign=sign*-1;
denom+=2;
}
cout << "pi value with 200 iterration: " << sum << endl;
sum=0.0,term;
denom=1,sign=1;
for(int i=0; i<300; i++){
term=4.0/denom;
term=term*sign;
//cout << term << endl;
sum=sum+term;
sign=sign*-1;
denom+=2;
}
cout << "pi value with 300 iterration: " << sum << endl;

system("pause");
}