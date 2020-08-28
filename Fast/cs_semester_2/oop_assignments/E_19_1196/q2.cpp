// Q2: pyramid
// By: 19L-1196 CS-2E1
// To: Hafiz Hamza
#include<iostream>
#include<iomanip> // only for setw
using namespace std;

int main(){

    int seed,random,levels,index,n_pyramids;
    cout << "Enter number of Pyramids: ";
    cin >> n_pyramids;
    // make 2e-array of row size pyramid and col size 4
    int **info_table = new int *[n_pyramids];// stores parameters
    int ***pyramids = new int **[n_pyramids];

    for(int i=0; i< n_pyramids; i++){

        // store this info in dynamic 2d-array
        *(info_table+i) = new int [4];
        cout << "Enter information for Pyramid # " << i+1 << endl;
        cout << "seed: ";
        cin >> seed;
        cout << "Levels: ";
        cin >> levels;
        cout << "Random number: ";
        cin >> random;
        cout << "Random number index: ";
        cin >> index;
        pyramids[i] = new int *[levels];
        //-----------------
        *(*(info_table+i)+0) = seed;
        *(*(info_table+i)+1) = levels;
        *(*(info_table+i)+2) = random;
        *(*(info_table+i)+3) = index;
        //------------------- base level

        pyramids[i][0] = new int [levels];
            for(int k=0; k < levels; k++){
                //pyramids[i][0][k] = seed *(k+1);
                *(*(*(pyramids+i)+0)+k) = seed*(k+1);
            }
            // add random number
            if(index < levels) // check
            *(*(*(pyramids+i)+0)+index) = random;
        //-------------------
        for(int j=1; j< levels; j++){
            //pyramids[i][j] = new int [levels-j];
            *(*(pyramids+i)+j) = new int [levels-j];
            for(int k=0; k < levels-j; k++){
                //pyramids[i][j][k] = (pyramids[i][j-1][k]) + (pyramids[i][j-1][k+1]);
                *(*(*(pyramids+i)+j)+k) = *(*(*(pyramids+i)+j-1)+k) + *(*(*(pyramids+i)+j-1)+k+1);
            }
        }

    }

    for(int i=0; i< n_pyramids; i++){
        levels = *(*(info_table+i)+1);
        cout << "pyramid # " << i+1 << endl << endl;
        for(int j=0; j< levels; j++){
            // print spaces
            for(int s=0; s < j; s++) cout << setw(5*j);
            for(int k=0; k< levels-j; k++){
                cout << *(*(*(pyramids+i)+j)+k) << setw(10);
            }
            cout << endl << endl;
        }
    }
    //--------------------- delete memory
    //--------------------- and set pointers to null
    for(int i=0; i< n_pyramids; i++){
        levels = *(*(info_table+i)+1);
            for(int j=0; j< levels; j++) delete []*(*(pyramids+i)+j);
        delete [](pyramids+i);
        delete *(info_table+i);
    }

    delete info_table;
    delete pyramids;

    pyramids = NULL;
    info_table=NULL;

    return 0;
}
