#include <iostream>
#include <fstream>
using namespace std;

void InputSongs(char fileName[50]);
void SearchSongByTitle(char title[100]);
bool contains(char str1[], char str2[]);
int main(){
	int choice=2;
	char song[50];
	while(choice != 0){
		cout << "0: to quit\n1: to search favorite song\n2: to list all songs\n";
		cin >> choice;
		if(choice == 1){
			cout << "enter your favorite song: ";
			cin.getline(song,50,'.');
			cout << "started searching...";
			SearchSongByTitle(song);
			cout << "ended searching ...";
		}
		if(choice==2){InputSongs("SongList.txt");}

	}

	system("pause");
}

void InputSongs(char fileName[50]){
	char songName[200], singer[100];
	int times;
	float duration;
	int numberOfSongs;
	ifstream songs;
	char temp;
	songs.open(fileName);
	if(songs.is_open()){
		songs >> numberOfSongs;
		for(int i=0; i< numberOfSongs; i++){
			songs >> duration;
			songs >> temp; //skipping comma;
			songs.getline(songName,200,',');
			songs.getline(singer,100,',');
			songs >> times;

			cout << duration << " " << songName << " " << singer << " " << times << " " << endl;

		}
	}
	else{
		cout << "cannot open SongsList" << endl;
	}

	songs.close();
}
//--------------------
void SearchSongByTitle(char title[100]){
	ofstream favorite;
	ifstream songs;
	favorite.open("FavouriteList.txt");
	songs.open("SongList.txt");

	char songName[200], singer[100];
	int times;
	float duration;
	int numberOfSongs;
	char temp;
	
	if(songs.is_open()){
		songs >> numberOfSongs;
		for(int i=0; i< numberOfSongs; i++){
			songs >> duration;
			songs >> temp; //skipping comma;
			songs.getline(songName,200,',');
			songs.getline(singer,100,',');
			songs >> times;
			if(contains(songName,title)){
			favorite << duration << " " << songName << " " << singer << " " << times << " " << endl;
			cout << "favorite songs are " << duration << " " << songName << " " << singer << " " << times << " " << endl;
			}
		}
	}
	else{
		cout << "cannot open SongsList" << endl;
	}

	songs.close();
	favorite.close();
}
//-------------------------
bool contains(char str1[], char str2[]){
	int s1_i=0, s2_i=0;
	bool found=false;
	while(str1[s1_i] != '\0' && str1[s1_i] != ' '){
		if(str1[s1_i]==str2[s2_i]){
			found=true;
			while(str2[s2_i] != '\0'){
				if(str2[s2_i] != str1[s1_i]) found=false;
				s2_i++;s1_i++;
				cout << "coming here..." << endl;
			}
		}

		s1_i++;
	}
	return found;
}