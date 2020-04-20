#pragma once
#include <iostream>
#include "employee.h"

using namespace std;     
class cabin {
	int cabinnumber;
	employee* emp;// 
public:
	cabin() {
		cabinnumber = 0;
		emp = nullptr;
	}
	cabin(int c) {
		cabinnumber = c;
		emp = nullptr;
	}
	void assignEmployee(employee* e){
		if (e != nullptr) {
			emp = e;
		}
		else { 
			emp = NULL;
		}
	}
	int getCabinNumber(){
		return cabinnumber;
	}
	employee* getAssignedEmployee() {
		return emp;
	}
	~cabin() {
		emp = nullptr;
	}
	void printcabininfo() {
		if (emp != nullptr ) {
			emp->printempinfo;
			cout << "Cabin Number of the employee is: " << cabinnumber<<endl;
		}
		else {
		
		}
	}
};
class Building {
	char* nameOfBuilding;
	int floornumber;
	int currentfloorcount;    
	int totalfloors;                               
	Floor** floorlist;
	//string name;
public:
	Building() {
		currentfloorcount = 0;
		totalfloors = 0;
		floornumber = 0;
		nameOfBuilding =0;
	}
	Building(const char* n, int x) {
		nameOfBuilding = new char[strlen(n)+1];                                                      
		strcpy_s(nameOfBuilding,strlen(n)+1,n);
		//floornumber = x;
		floorlist = new Floor*[x];
		currentfloorcount=0;
		totalfloors =x;
	}      //
	bool buildfloor(int i) {
		if (currentfloorcount < totalfloors) {
			floorlist[currentfloorcount++]= new Floor(i);
			//floorlist[currentfloorcount++] = newfloor;
			return true;
		}
		else return false;                          
	}																													
	int& getnooffloors() {
		return currentfloorcount;
}
	bool buildroom(int rN) {
		if(currentfloorcount< totalfloors){
			floorlist[currentfloorcount++] = new Floor(rN);
			return true;
		}
		return false;
	}
	int getnoofrooms(int f) {                   
														
		return floorlist[f]->getnoofrooms();			 
													
	int getnoofcabins(int f, int r) {            
		return floorlist[f]->getnoofcabins(r);	
    } 														/*comment here
																	
																		   */
	cabin* getCabin(int c,int r, int f){		
		return floorlist[f]->getcabin(r,c);
	}
	void addcabin(int i, int j, cabin* c) {
		floorlist[j]->addcabin(i,c);
	}

	employee*& getassignedemployee(int c,int r,int f){
	}
	~Building(){ 
		for(int i=0;i<currentfloorcount;i++){
			delete  floorlist[i];
		}
		delete[] floorlist;
	}
};
class employee {
private:
	int IDemp;
	char* empName;
public:
	employee(int id,const char* n){
		
		if (n != NULL) {
			IDemp = id;
			empName = new char[strlen(n) + 1];
			strcpy_s(empName, strlen(n) + 1, n);
		}
		else{
			empName = NULL;
			IDemp = 0;
			}

		}

	char*& getEmployeeName(){
		return empName;
	}
	int& getIdofEmp(){
		return IDemp;
	}
	~employee(){
		if(empName!=NULL){
			delete []empName;
			empName=NULL;
		}
		else{
			empName=NULL;
		}
		
	}
	void printempinfo() {
		if (empName != NULL && IDemp != 0) {
			cout << empName << ":" << IDemp << endl;
		}
		else{
			
			cout << "info not found!" << endl;
		}	
	}
 
};
class room {
	int roomnumber;
	int totalcabins;
	int currentcabincount;
	cabin cabinnumber;
	cabin** cabinlist;
public:
	room() {
		currentcabincount=0;
	}
	room(int r) {
	currentcabincount=r	;
	}
	bool addcabin() {
		if (currentcabincount < totalcabins) {
			cabin* newcabin = new cabin(cabinnumber);
			cabinlist[currentcabincount++] = newcabin;
			return true;
		}
		else
			return false;
	}
	int getnoofcabins() {
		 return currentcabincount ;
	}
	int getRoomNumber(){
		return roomnumber;
	}
};
class Floor {
	int numberofrooms;
	room roomnumber;
	int totalrooms;
	int floornumber;
	int currentroomcount;
	room** roomlist;
public:
	Floor() {}
	Floor(int x) {
		roomlist = new room * [x];
		totalrooms = x;
		//numberofrooms = x;
		currentroomcount = 0;
	}
	//
	bool buildroom();
	int getnoofrooms();
	
	int getnoofcabins(int r) {
		for (int i = 0; i < currentroomcount; i++) {
			if (roomlist[i]->getRoomNumber == r) {
				return roomlist[i]->getnoofcabins();
			}
		}
	}
	bool addcabin(int r,cabin*c){
		for(int i=0;i<currentroomcount;i++){
			if(roomlist[i]->getRoomNumber()==r){
				// roomlist[i]->addcabin(c);
				return true;
			}
		}
		return false;
	}	

};	

bool Floor::buildroom() {
	if (currentroomcount < totalrooms) {
		//room *newroom = new room(floornumber);
		roomlist[currentroomcount++] = new room;
		return true;
	}
	else return false;
}
int Floor::getnoofrooms() {
	return currentroomcount;
}
