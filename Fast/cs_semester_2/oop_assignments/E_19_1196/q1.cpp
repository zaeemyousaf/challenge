// 19L-1196
// section BSCS-2E1
// To: Hafiz Muhammad Hamza
// Assignment 1 OOP
#include <iostream>
void sort(int *&, int );
// array, size
void Union(int *&, int *&, int, int, int *&, int &);
// A, B, A_size,B_size, union_ptr, union_size
void Intersection(int *&, int *&, int, int, int *&, int &);
// A, B, A_size,B_size, intersection_ptr, inter_size
void fill_array(int *&,int);
// Array, its_size
void disp_array(int *, int,const char []);
// Array, its_size, its_label
using namespace std;
int main()
{
    int a_size=0, b_size=0,Size = 0;
    cout << "enter size of set A: ";
    cin >> a_size;
    cout << "enter size of set B: ";
    cin >> b_size;

    int *a_ptr = new int[a_size];
    int *b_ptr = new int[b_size];
    int *c_ptr;

    cout << "Enter elements of Set A\n";
    fill_array(a_ptr,a_size);

    cout << "Enter elements of Set B\n";
    fill_array(b_ptr,b_size);

    Union(a_ptr,b_ptr,a_size,b_size,c_ptr,Size);
    sort(c_ptr,Size);

    disp_array(a_ptr, a_size,"A");
    disp_array(b_ptr, b_size,"B");
    cout << "A Union B ";
    disp_array(c_ptr,Size,"");

    delete c_ptr;
    //----------------------intersection
    Intersection(a_ptr,b_ptr,a_size,b_size,c_ptr,Size);
    sort(c_ptr,Size);

    cout << "A Intersection B";
    disp_array(c_ptr,Size,"");


    delete a_ptr;
    delete b_ptr;
    delete c_ptr;

    system("pause");
    return 0;
}
//------------------
void sort(int *&arr, int size){
    //bubble sort
    for(int i=0; i< size-1; i++){
        bool swap=false;
        for(int j=0; j< (size-i-1);j++){
            if( *(arr+j) > *(arr+j+1)){
                int temp=*(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = temp;
                swap = true;
            }
        }void fill_array(int *&,int);
        if(! swap) break;
    }
}
//----------------------
void Union(int *&A, int *&B, int a_size, int b_size, int *&C, int &size){
    // copy unique elements into C
    int c_index=0;
    int *u = new int [a_size+b_size]; // max possible size
    // it will be shrunk if needed at the end of function
    bool found;
    //----------------------copying array a into c
    for(int i=0; i< a_size; i++){
        found=false;
        //set contains only one occurance
        for(int j=0; j< c_index ; j++){
            if ( *(u+j) == *(A+i)) {
                found=true;break;
            }
        }
        if (! found) {
            // if it is unique element then insert
            //u[c_index++]=A[i];
            *(u+c_index++) = *(A+i);
        }
    }
    //----------------- copying array b
    for(int i=0; i< b_size; i++){
            found=false;
        for(int j=0; j< c_index ; j++){
            if ( *(u+j) == *(B+i)) {
                found=true;break;
            }
        }
        if (! found) {
            //u[c_index++]=B[i];
            *(u+c_index++) = *(B+i);
        }
    }
    size=c_index;

    int *final_arr = new int [size]; // shrinking array
    for(int i=0; i< size; i++) *(final_arr+i) = *(u+i);
    C=final_arr;
    delete u; //no need to NULL the ptr because it will die itself
}
//----------------------------------
void Intersection(int *&A, int *&B, int a_size, int b_size, int *&C, int &size){
    // copy unique and common elements elements into C
    int c_index=0,max_size;
    max_size = (b_size > a_size)? a_size:b_size;
    int *u = new int [max_size];
    // max possible size is the size of small array
    bool found,common;

    for(int i=0; i< a_size; i++){
        found=false;
        for(int j=0; j< c_index ; j++){
            if ( *(u+j) == *(A+i)) {
                found=true;
                break;
            }
        }
        if (! found) {
            common=false;
            for(int k=0; k< b_size; k++){
                if(*(A+i)== *(B+k)){common=true; break;}
            }
            if(common){
                // if it is common in both then inset into array
                //u[c_index++]=A[i];
                *(u+c_index++) = *(A+i);
            }
        }
    }

    size=c_index;
    //cout << "size is " << size << endl;
    int *final_arr = new int [size];
    for(int i=0; i< size; i++) final_arr[i] = u[i];
    C=final_arr;
    delete u; // no need to NULL the ptr which will die itself

}
//-------------------------------
void fill_array(int *&arr,int size){
    for(int i=0; i< size; i++){
        cout << "Element# " << i << ": ";
        cin >> *(arr+i);
    }
}
//--------------------------------
void disp_array(int *arr, int size, const char name[10]){
    cout << name << " = {";
    for(int i=0; i< size; i++) {
        cout << *(arr+i);
        if(i < size -1) cout << ",";
    }
    cout << "}" << endl;
}
