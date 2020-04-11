#include <iostream>
//19L-1196
//zaeem
//Date & time difference
using namespace std;
int datediff(int, int, int, int,int , int, int &, int &,int &);
int timediff(int, int, int, int, int, int, int &, int &, int &);


bool isleap(int );
int m2d(int, bool); // month to days conversion
// bool: 1 means that it is leap year
int main(){
    int y1,y2,m1,m2,d1,d2,y,m,d,days;
    int h1,h2,M1,M2,s1,s2,h,M,s,seconds,choice;
    cout << "Select your choice: \n1: \Difference of date\n2:Difference of time\n3:Exit\n";
    cin >> choice;
    while(choice !=3){
    switch(choice){
case 1:
    cout << "Enter date 1 e.g: year Month Days. ";
    cin >> y1>>m1>>d1;
    cout << "Enter date 2 e.g: year Month Days. ";
    cin >> y2>>m2>>d2;

    days = datediff(y1,m1,d1,y2,m2,d2,y,m,d); //calling
    cout << "Total Days: " << days << endl;
    cout  << "Years: " << y << "\nMonths: " << m << "\nDays: " << d << endl;
    break;
case 2:
        cout << "Enter greater time e.g: Hours Minutes Seconds. ";
        cin >> h1>>M1>>s1;
        cout << "Enter smaller time e.g: Hours Minutes Seconds. ";
        cin >> h2>>M2>>s2;
    seconds = timediff(h1,M1,s1,h2,M2,s2,h,M,s); //calling
    cout << "Seconds: " << seconds << endl;
    cout << "Time difference: Hours: " << h << " Minutes: " << M << " Seconds: " << s << endl;
break;
    }
    cout << "Select your choice: \n1: \Difference of date\n2:Difference of time\n3:Exit\n";
    cin >> choice;

    }

return 0;
}
int datediff(int y2, int m2, int d2, int y1,int m1, int d1, int &yd, int &md,int &dd){
int total_middle_years = (y2 -y1 >0)? y2-y1+1:0; //inclusive: +1

int over_days_y2=d2;
int over_days_y1=d1;
bool leap_y2=isleap(y2);
bool leap_y1=isleap(y1);
int days_of_month;
//---------------
for(int m=1; m < m2; m++){
days_of_month = m2d(m,leap_y2);
over_days_y2 = over_days_y2 + days_of_month;
}
//---------------
for(int m=1; m < m1; m++){
days_of_month = m2d(m,leap_y1);
over_days_y1 = over_days_y1 + days_of_month;
}
//----------------
y2=y2-1; //over days have been computed
y1=y1-1;// hence reduce the year
//----------------
int intutive_leap_years_y2 = y2/4;
int intutive_leap_years_y1 = y1/4;
//cout << intutive_leap_years << " intutive leap years." << endl;
int centuries_y2 = y2/100;
int centuries_y1 = y1/100;
//-----------------------------
int leap_centuries_y2 = y2/400;
int leap_centuries_y1 = y1/400;

int leap_years_y2=intutive_leap_years_y2 - centuries_y2 + leap_centuries_y2;
int non_leap_years_y2 = y2 - leap_years_y2;
// leap year has 366 days; while other has 365 days
int total_days_y2 = leap_years_y2*366+ non_leap_years_y2*365+ over_days_y2;
//------------------------
int leap_years_y1=intutive_leap_years_y1 - centuries_y1 + leap_centuries_y1;
int non_leap_years_y1 = y1 - leap_years_y1;
// leap year has 366 days; while other has 365 days
int total_days_y1 = leap_years_y1*366+ non_leap_years_y1*365+over_days_y1;
int days_dif=total_days_y2-total_days_y1;
if(days_dif <0) days_dif=days_dif*-1; // taking absolute
// updating the reference parameter
int n_days=days_dif;
yd = n_days / 365;
n_days = n_days %365;
md = n_days/30.4167;
n_days = n_days - (md*30.4167);
dd = n_days;
return days_dif;
}


int m2d(int m, bool leap){
int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(leap && m==2){return months[1]+1;}
    else if(m >0 && m <= 12){return months[m-1];}
    else{return 0;}
}
//--------------------------isleap
bool isleap(int y){
if(y % 4 == 0 && y %100 !=0 || y % 400 ==0) return true;
else return false;
}
//-----------------------timdiff
int timediff(int h1,int m1, int s1, int h2, int m2, int s2, int & hd, int & md, int & sd){
if(s1 - s2 >=0){sd=s1-s2;}
else{sd=60+s1-s2; m1--; // minutes is reduced by one after carry
}
if(m1-m2 >= 0){md=m1-m2;}
else{md=60+m1-m2; h1--;}
hd=h1-h2;
return (hd*3600+md*60+sd);
}
