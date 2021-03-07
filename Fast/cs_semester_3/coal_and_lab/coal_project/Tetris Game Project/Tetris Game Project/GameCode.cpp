#include "Tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <iostream>
#include <ctime>
using namespace std;

//void Download()
//{
//	for (int i = 1; i <= 50; i++)
//	{
//		showConsoleCursor(false);
//		system("CLS");
//		setxy(55, 12);
//		cout << "Loading ";
//
//		for (int j = 1; j <= i; j++)
//		{
//			setxy(33 + j, 14);
//			cout << char(219);
//		}
//		cout << 2 * i << "%";
//		if (i >= 1 && i <= 20)
//		{
//			setxy(45, 16);
//			cout << "Creating Temporary files";
//		}
//		else if (i >= 20 && i <= 40)
//		{
//			setxy(45, 16);
//			cout << "Accessing Main Memory";
//		}
//		else if (i >= 40 && i <= 48)
//		{
//			setxy(45, 16);
//			cout << "Accessing Cache";
//		}
//		else
//		{
//			setxy(55, 16);
//			cout << "Complete. ";
//		}
//		delaay(1);
//	}
//	delaay(10);
//	cout << endl;
//	cout << "Press Enter to Continue \n";
//	_getch();
//}
//void Congratulations()
//{
//	showConsoleCursor(false);
//	//C
//	drawLine(80, 100, 170, 100, 200, 120, 120);
//	drawLine(100, 115, 170, 115, 250, 120, 120);
//	drawLine(170, 100, 170, 115, 195, 185, 57);
//	drawLine(80, 100, 80, 250, 250);
//	drawLine(100, 115, 100, 235, 250);
//	drawLine(80, 250, 170, 250, 210, 230, 0);
//	drawLine(100, 235, 170, 235, 250);
//	drawLine(170, 250, 170, 235, 198, 65, 32);
//
//	//O
//	drawRectangle(210, 150, 255, 250, 250, 25, 150);
//
//	//N
//	drawLine(290, 150, 290, 250, 210, 20, 210);
//	drawLine(290, 150, 330, 250, 20, 210, 150);
//	drawLine(330, 150, 330, 250, 200, 20, 210);
//
//	//G
//	drawLine(350, 150, 350, 250, 210, 20, 210);
//	drawLine(350, 150, 380, 150, 200, 25, 59);
//	drawLine(350, 250, 380, 250, 200, 25, 59);
//	drawLine(380, 200, 380, 250, 210, 20, 210);
//	drawLine(375, 200, 380, 200, 200, 25, 59);
//
//	//R
//	drawLine(395, 150, 395, 250, 240, 21, 39);
//	drawLine(395, 150, 425, 150, 210, 25, 255);
//	drawLine(395, 200, 425, 200, 21, 150, 150);
//	drawLine(425, 150, 425, 200, 210, 35, 100);
//	drawLine(395, 200, 425, 250, 250, 150, 140);
//
//	//A
//	drawLine(445, 250, 460, 150, 210, 255, 32);
//	drawLine(460, 150, 475, 250, 200, 32, 58);
//	drawLine(450, 195, 470, 195, 54, 98, 37);
//
//	//T
//	drawLine(490, 150, 520, 150, 240, 250, 10);
//	drawLine(505, 150, 505, 250, 250, 154, 168);
//
//	//U
//	drawLine(530, 150, 530, 250, 210, 250, 289);
//	drawLine(530, 250, 555, 250, 250, 154, 165);
//	drawLine(555, 150, 555, 250, 255, 120, 100);
//
//	//L
//	drawLine(570, 150, 570, 250, 210, 250, 265);
//	drawLine(570, 250, 600, 250, 210, 250, 265);
//
//	//A
//	drawLine(610, 250, 625, 150, 210, 250, 145);
//	drawLine(625, 150, 640, 250, 210, 250, 100);
//	drawLine(615, 195, 635, 195, 145, 250, 189);
//
//	//T
//	drawLine(655, 150, 685, 150, 210, 178, 98);
//	drawLine(670, 150, 670, 250, 210, 78, 98);
//
//	//I
//	drawLine(700, 150, 710, 150, 210, 78, 64);
//	drawLine(700, 250, 710, 250, 78, 98, 250);
//	drawLine(705, 150, 705, 250, 58, 78, 98);
//
//	//O
//	drawRectangle(730, 150, 775, 250, 210, 78, 54);
//
//	//N
//	drawLine(795, 150, 795, 250, 154, 68, 52);
//	drawLine(795, 150, 835, 250, 75, 154, 32);
//	drawLine(835, 150, 835, 250, 190, 54, 21);
//
//	//S
//	drawLine(850, 150, 870, 150, 150, 54, 15);
//	drawLine(850, 150, 850, 200, 162, 98, 65);
//	drawLine(850, 200, 870, 200, 154, 87, 65);
//	drawLine(870, 200, 870, 250, 117, 78, 65);
//	drawLine(850, 250, 870, 250, 198, 35, 255);
//
//	drawLine(60, 285, 890, 285, 255, 120, 150);
//	drawLine(80, 295, 870, 295, 210, 150, 187);
//
//	cout << "Press Enter to Continue \n";
//	_getch();
//}
//void GameOver()
//{
//	showConsoleCursor(false);
//
//	//G
//	drawLine(100, 70, 100, 250, 210, 250, 15);
//	drawLine(100, 70, 150, 70, 245, 87, 98);
//	drawLine(100, 250, 150, 250, 287, 156, 98);
//	drawLine(150, 175, 150, 250, 185, 89, 65);
//	drawLine(140, 175, 160, 175, 65, 98, 78);
//
//	//A
//	drawLine(170, 250, 185, 150, 210, 178, 98);
//	drawLine(185, 150, 200, 250, 178, 210, 98);
//	drawLine(175, 195, 195, 195, 154, 87, 98);
//
//	//M
//	drawLine(215, 150, 215, 250, 210, 250, 15);
//	drawLine(215, 150, 230, 250, 185, 89, 65);
//	drawLine(230, 250, 245, 150, 245, 87, 98);
//	drawLine(245, 150, 245, 250, 287, 156, 98);
//
//	//E
//	drawLine(260, 150, 260, 250, 65, 187, 250);
//	drawLine(260, 150, 285, 150, 210, 54, 98);
//	drawLine(260, 200, 275, 200, 245, 87, 98);
//	drawLine(260, 250, 285, 250, 24, 87, 255);
//
//	//O
//	drawEllipse(480, 70, 590, 250, 210, 65, 87);
//
//	//V
//	drawLine(610, 150, 625, 250, 254, 98, 78);
//	drawLine(625, 250, 640, 150, 187, 45, 98);
//
//	//E
//	drawLine(655, 150, 655, 250, 210, 54, 87);
//	drawLine(655, 150, 680, 150, 287, 189, 65);
//	drawLine(655, 200, 670, 200, 245, 78, 89);
//	drawLine(655, 250, 680, 250, 178, 89, 45);
//
//	//R
//	drawLine(695, 150, 695, 250, 287, 89, 32);
//	drawLine(695, 150, 720, 150, 287, 98, 78);
//	drawLine(695, 200, 720, 200, 98, 78, 45);
//	drawLine(720, 150, 720, 200, 210, 254, 87);
//	drawLine(695, 200, 720, 250, 287, 54, 65);
//
//	drawLine(60, 260, 290, 260, 289, 52, 87);
//	drawLine(70, 270, 285, 270, 287, 87, 98);
//	drawLine(465, 260, 735, 260, 289, 52, 87);
//	drawLine(465, 270, 720, 270, 287, 87, 98);
//	drawRectangle(290, 260, 465, 270, 210, 65, 98, 210, 98, 65);
//
//	cout << "Press Enter to Continue \n";
//	_getch();
//}

int main()
{
	srand((unsigned)time(0));
	//system("Color B5");
	/*Download();
	system("cls");
	Congratulations();
	system("cls");
	GameOver();*/
	bool endgame = true;

	Piece_O temp;

	Piece_L l;
	Piece_S s;
	Piece_Z z;
	Piece_O o;
	Piece_I i;
	Piece_J j;
	Piece_T t;

	int count = 0;
	Board b(12, 19);
	while (endgame)
	{
		int random = (rand() % 7);
		if (random == 0) {
			l.print();
		}
		else if (random == 1) {
			s.print();
		}
		else if (random == 2) {
			z.print();
		}
		else if (random == 3) {
			o.print();
		}
		else if (random == 4) {
			i.print();
		}
		else if (random == 5) {
			l.print();
		}
		else if (random == 6) {
			t.print();
		}
	}

	system("pause");
	return 0;
}