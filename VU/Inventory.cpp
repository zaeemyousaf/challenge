#include <iostream>
#include <fstream>
using namespace std;

class Inventory
{
private:
  int itemID;
  char itemName[20];
  float itemPrice;
  float quantity;
  float totalPrice;
public:
  void readItem();
  void displayItem();
  int getItemID();
  char* getItemName();
  float getPrice();
  float getQuantity();
  void updateQuantity(float q);
};

void Inventory::readItem(){
  cout << "please enter Item id: ";
  cin >> itemID;
  cout << "please enter Item name: ";
  cin >> itemName;
  cout << "please enter price: ";
  cin >> itemPrice;
  cout << "please enter quantity: ";
  cin >> quantity;
  totalPrice = quantity*itemPrice;

  cout << "Inventory record(s) added susccessfully.\n";
}

void Inventory::displayItem(){
  cout << "Item id:" << itemID << "\t";
  cout << "Item name:" << itemName << "\t";;
  cout << "Item price:" <<  itemPrice << "\t";;
  cout << "Quantity:" << quantity << "\t";;
  cout << "TotalPrice:" << totalPrice;
  cout << endl;
}

int Inventory::getItemID(){ return itemID;}
char* Inventory::getItemName(){ return itemName;}
float Inventory::getPrice(){return itemPrice;}
float Inventory::getQuantity(){return quantity;} 
void Inventory::updateQuantity(float q){}

//Deleting existing file
void deleteExistingFile(){
  remove("inventory.txt");
  rename("temp.txt","inventory.txt");
}
//appending item in file
void appendToFile(){
    Inventory inv;
    inv.readItem();    
    //inv.displayItem();
    //open file for appending
    ofstream fout("inventory.txt", ios::app); // append mode
    fout << inv.getItemID() << ' ';
    fout << inv.getItemName() << ' ';;
    fout << inv.getPrice() << ' ';;
    fout << inv.getQuantity()<< '\n';
    fout.close();

}
//display items
void displayAll(){
    ifstream fin("inventory.txt", ios::in); // read mode
    int itemID;
    char itemName[20];
    float itemPrice;
    float quantity;
    float totalPrice;

    fin >> itemID;
    fin >> itemName;
    fin >> itemPrice;
    fin >> quantity;
    totalPrice = itemPrice*quantity;

    while(!fin.eof()){
    cout << "Item id:" << itemID << "\t";
    cout << "Item name:" << itemName << "\t";;
    cout << "Item price:" <<  itemPrice << "\t";;
    cout << "Quantity:" << quantity << "\t";;
    cout << "TotalPrice:" << totalPrice;
    cout << endl;

    fin >> itemID;
    fin >> itemName;
    fin >> itemPrice;
    fin >> quantity;
    totalPrice = itemPrice*quantity;

    }
    fin.close();
}
//increasing quantity of item
void increaseQuantity(){
    
  //copy data into new_file till id matches
  //insert updated data
  // insert remaining data
  // delete old file
  // rename new_file

  //  deleteExistingFile();

  int id;
  int new_quantity;
  cout << "Enter item id: ";
  cin >> id;
  cout << "add quantity: ";
  cin >> new_quantity;
  
  ifstream fin("inventory.txt",ios::in);
  ofstream fout("temp.txt", ios::out); // write mode
    int itemID;
    char itemName[20];
    float itemPrice;
    float quantity;
    float totalPrice;

    fin >> itemID;
    fin >> itemName;
    fin >> itemPrice;
    fin >> quantity;

    while(!fin.eof()){
      if(itemID == id){
	fout << itemID << ' ';
	fout << itemName << ' ';;
	fout << itemPrice << ' ';;
	fout << quantity+new_quantity<< '\n';
      }
      else{
	fout << itemID << ' ';
	fout << itemName << ' ';;
	fout << itemPrice << ' ';;
	fout << quantity<< '\n';

      }

      fin >> itemID;
      fin >> itemName;
      fin >> itemPrice;
      fin >> quantity;
    }
    fout.close();
    fin.close();
    deleteExistingFile();
    cout << "Item quantity updated successfully\n";
}
//display optionMenu
void displayOptions(){
  cout << "Enter choice\n";
  cout << "1- ADD AN INVENTORY ITEM\n";
  cout << "2- DISPLAY FILE DATA\n";
  cout << "3- INCREASE QUANTITY\n";
  cout << "Please select a choice: ";
}
int main(){
  char exit; // y/n
  do{
  int choice;
  displayOptions();
  cin >> choice;

  switch(choice){
  case 1:
    {
    // add an inventory item here
      appendToFile();
    }
    
    break;
  case 2:
    // display file data
    {
      displayAll();
    }
    break;
  case 3:
    increaseQuantity();
    break;

  default:
    cout << "invalid choice\n";
 
  }

  cout << "Do you want to continue? y/n: ";
  cin >> exit;  
  }
  while(exit == 'y');  
}
