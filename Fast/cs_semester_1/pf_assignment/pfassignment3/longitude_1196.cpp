#include <iostream>
//19L-1196
//zaeem yousaf
//Longitude and latitude
using namespace std;
void geo_coord_to_decimal(int,int,int,int,int,int,float &,float &);
int main()
{
float latitude,longitude;
int d,d1,m,m1,s,s1;
cout << "Enter Latitude e.g degree minutes seconds: ";
cin >> d>>m>>s;
cout << "Enter Longitude e.g degree minutes seconds: ";
cin >> d1>>m1>>s1;

geo_coord_to_decimal(d,m,s,d1,m1,s1,latitude,longitude);
cout << "latitude: " << latitude << " longitude: " << longitude << endl;
    return 0;
}
void geo_coord_to_decimal(int lat_d,int lat_m, \
        int lat_s,int long_d, int long_m, int long_s, float &lati,float &longi){
    lati= (lat_d * 3600  + lat_m*60+lat_s)/3600.0;
    longi= (long_d * 3600 + long_m*60+long_s)/3600.0;

        }
