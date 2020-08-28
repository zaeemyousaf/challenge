//19L-1196
//Lab Assignment: Q1..Q7
#include <iostream>
using namespace std;
// function prototypes start
int ** AllocateMemory(int &, int &);
void InitializeMatrix(int **,const int &, const int &);
void DisplayMatrix(int **, const int &, const int &);
void DeallocateMemory(int **, const int &);
int * maxCol(int **,int, int);
bool isMatrixUpperTriangular(int **,int, int);
int myTokenizer(char *, char **&, char);
void printTokens(char **,int);
// function prototypes ends

int main(){

	int rows,cols;
	int ** Array;
	Array = AllocateMemory(rows, cols);
	InitializeMatrix(Array, rows,cols);
	DisplayMatrix(Array, rows,cols);
	int *maxs = new int [cols];
	maxs = maxCol(Array, rows, cols);
	cout << "max from each cols...\n";
	for(int i=0; i< cols; i++) cout << *(maxs+i) << " ";
	cout << endl;
	cout << "checking if it is upper triangular ...\n";
	if(isMatrixUpperTriangular(Array,rows,cols)){
		cout << "it is upper triangular\n";
	}
	else{cout << "not upper triangular ...\n";}

    //----------------- Q 7
    cin.ignore();
    char str[100],delim;
    int n_tokens;
    cout << "enter a string to tokenize it: ";
    cin.getline(str,100);
    //cin.ignore();
    cout << "enter a delimeter of of one char ";
    cin >> delim;
    char **token_list;
    n_tokens = myTokenizer(str,token_list,delim);
    printTokens(token_list,n_tokens);

    // delete memory of tokenizer
	for(int i=0; i< n_tokens; i++) delete []*(token_list+i);
	delete []token_list;

	DeallocateMemory(Array,rows);
    system("pause");

}
//---------
int ** AllocateMemory(int &rows, int &cols){
	int r,c;
	cout << "Enter rows: ";
	cin >> r;
	cout << "Enter cols: ";
	cin >> c;
	rows=r;
	cols=c;
	int ** address = new int *[rows];
	for(int i=0; i < cols; i++){
		*(address+i) = new int [cols];

	}
	return address;
}
// advantage: lesser data movement
// only address is passed instead of heavy data

void InitializeMatrix(int **arr,const int &rows, const int &cols){
	for(int i=0; i< rows; i++){
		for(int j=0; j < cols; j++){
			cout << "enter element: ";
			cin >> *(*(arr+i)+j);
		}
	}

}
// why are we passing parameter as const
// we don't want the function to change our values
void DisplayMatrix(int **arr, const int & rows, const int & cols){
	for(int i=0; i< rows; i++){
		for(int j=0; j< cols; j++){
			cout << *(*(arr+i)+j) << " ";
		}
		cout << endl;

	}


}
//----------------------
inline void DeallocateMemory(int **arr, const int &rows){
	for(int i=0; i< rows; i++){

		delete [] *(arr+i);
		//cout << (arr+i);
		cout << "\n\ndeallocating columns...\n";

	}
	delete []arr;
	cout << "deallocating rows...\n";


}
//----------------

int * maxCol(int **arr,int rows, int cols){
	// will return a pointer to an array
	int *max_col = new int [cols];
	for (int j=0; j< cols; j++){
		int max=*(*(arr+0)+j);
		for(int i=0; i< rows; i++){
			if( *(*(arr+i)+j) > max)
				max=*(*(arr+i)+j);

		}
		*(max_col+j) = max;
	}
	return max_col;

}
//-----------------------
bool isMatrixUpperTriangular(int **arr,int rows, int cols){
	bool upperTriangular=true;
	for(int i=1; i < rows; i++){
		for(int j=0; j< i; j++){
			if(*(*(arr+i)+j) != 0)
			upperTriangular = false;
		}
	}
	return upperTriangular;
}
//----------------------
int myTokenizer(char *data, char **&list_tokens, char delim){
    //count delimeters so that to make n rows
    int n_delimeters=0, ri=0;//read index
    while (*(data + ri) != '\0'){
        if( *(data+ ri++) == delim) n_delimeters++;
    }

    char **lines = new char *[n_delimeters];
    int n_tokens,i=0, token_index=0;
    char token[32];
    int token_length=0;
    while ( *(data+i) != '\0'){
        if( *(data+i) != delim){
            token[token_length]=*(data+i); // keep on recording until delim
            token_length ++;
        }
        else{
            //cout << "progress...\n";
            token_index=0;
            *(lines+n_tokens) = new char [token_length+1]; // 1 for \0
            //copy the token in dynamic array
            int j;
            for(j=0; j< token_length; j++){
                *(*(lines+n_tokens)+j) = token[j];
            }
            *(*(lines+n_tokens)+j) = '\0';
            n_tokens++;
            token_length=0;

        }
        i++;
    }
    //copy last word as well

    if(token_length!=0){
            //cout << "progress...\n";
            token_index=0;
            *(lines+n_tokens) = new char [token_length+1]; // 1 for \0
            //copy the token in dynamic array
        // add last token
        int j=0;
        for(; j< token_length; j++){
                *(*(lines+n_tokens)+j) = token[j];
        }
        *(*(lines+n_tokens)+j) = '\0';

    }
    n_tokens++;
    list_tokens = lines;
    return n_tokens;
}
//---------------------
void printTokens(char **token_list,int size){
    for(int i=0; i< size; i++) cout << *(token_list+i) << endl;
}
