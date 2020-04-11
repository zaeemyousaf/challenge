#include <iostream>
#include "mystring.h"
using namespace std;

MyString::MyString(){
	str = nullptr;
	strLength=0;
}

//------------------------
MyString::MyString(const char * str1)
{
	int si=0;
	while (str1[si] != '\0'){
		si++;
	}

	str = new char [si+1];
	for(int i=0; i< si; i++) str[i] = str1[i];
	str[si]='\0';
	strLength = si;
}

//---------------------------

MyString::MyString(const MyString& str_obj)
{
	int si=0;
	while (str_obj.str[si] != '\0'){
		si++;
	}

	str = new char [si+1];
	for(int i=0; i< si; i++) str[i] = str_obj.str[i];
	str[si]='\0';
	strLength = si;
}

//----------------------------

void MyString::assign(const MyString obj)
{
	delete str;
	int si=0;
	while(obj.str[si] != '\0') si++;
	str = new char [si+1];
	for(int i=0; i < si; i++) str[i] = obj.str[i];
	str[si]='\0';
	strLength = si;
}

//---------------------
void MyString::assign(const char *str1)
{
	delete str;
	int si=0;
	while(str1[si] != '\0') si++;
	str = new char [si+1];
	for(int i=0; i < si; i++) str[i] =str[i];
	str[si]='\0';
	strLength = si;
}

//--------------------
void MyString::display(){
	if( str != nullptr) cout << str << endl;
	else{cout << "" << endl;}
}

//--------------------
int MyString::getLength(){
	return strLength;
}

//---------------------------------
void MyString::append(char const *str1){
	if(str != nullptr){
	int si1=0,s2=strLength;
	while(str1[si1] != '\0') si1++;
	
	char *temp = new char [si1+s2+1];
	//cout << si1+s2+1 << endl;
	for(int i=0; i< s2; i++) temp[i]=str[i];
	for(int i=s2,j=0; i< si1+s2;  i++) temp[i] =str1[j++];
	temp[si1+s2] = '\0';

	delete str;
	str = temp;
	}

}

//---------------------------
void MyString::append(const MyString &obj){
	if(str != nullptr){
	int si1=0,s2=strLength;
	while(obj.str[si1] != '\0') si1++;
	
	char *temp = new char [si1+s2+1];
	//cout << si1+s2+1 << endl;
	for(int i=0; i< s2; i++) temp[i]=str[i];
	for(int i=s2,j=0; i< si1+s2;  i++) temp[i] =obj.str[j++];
	temp[si1+s2] = '\0';

	delete str;
	str = temp;
	}


}

//----------------------------
int MyString::compareTo(const char *str1){
	if(str != nullptr){
		int si=0,si1=0; // si1 index of str1
		while(str1[si1] != '\0' && str[si1] !='\0'){
			if(str1[si1] > str[si1]) return -1;
			else if(str[si1] > str1[si1]) return 1;
			si1++;
		}
		if(str1[si1] > str[si1]) return -1;
		else if(str[si1] > str1[si1]) return 1;
		else return 0;

	}

}

//--------------------------
int MyString::compareTo(const MyString obj){
	if(str != nullptr){
		int si=0,si1=0; // si1 index of str1
		while(obj.str[si1] != '\0' && str[si1] !='\0'){
			if(obj.str[si1] > str[si1]) return -1;
			else if(str[si1] > obj.str[si1]) return 1;
			si1++;
		}
		if(obj.str[si1] > str[si1]) return -1;
		else if(str[si1] > obj.str[si1]) return 1;
		else return 0;

	}

}

//------------
MyString::~MyString(){
	delete str;
	str = nullptr;
}



int main(){
	MyString s1;
	s1.display();
	s1.assign("assigned string by const string");
	s1.display();
	cout << "assigning by object\n";
	s1.assign(s1);
	s1.display();
	MyString s2("this is string");
	s2.display();
	MyString s3(s2);
	s3.display();
	s3.append("appended string");
	s3.display();
	s3.append(s2);
	s3.display();
	cout << s2.compareTo("this is string");
	cout << s2.compareTo(s3);
	system("pause");
}