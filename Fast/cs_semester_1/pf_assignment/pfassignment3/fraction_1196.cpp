#include <iostream>
//19L-1196
// zaeem
//Reducing Fraction
int reduce_fraction(int, int);
//1st & stores: reduced numerator=
using namespace std;

int main()
{
int a,b;
cout << "enter numerator space denominator: ";
cin >> a >> b;
bool success;
reduce_fraction(a,b);
return 0;

}

int reduce_fraction(int num, int denom){
    int hcf,smaller,greater,n,d;
if(num <=0 || denom <=0){
        cout << "failed to reduce.\n";
        return 0;}
else{
    greater=(num > denom)? num: denom;
    smaller=(num < denom)? num: denom;

            int r=greater % smaller;
            while(r!=0){
                greater=smaller;
                smaller=r;
                r=greater % smaller;
            }
            hcf=smaller;
    }
    n=num/hcf;
    d=denom/hcf;
cout << num << " / " <<denom << " = " << n << " / " <<d;
return 1;
}
