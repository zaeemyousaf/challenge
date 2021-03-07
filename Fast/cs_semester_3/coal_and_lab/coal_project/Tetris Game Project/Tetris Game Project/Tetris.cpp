#include "Tetris.h"
#include "mygraphics.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <iostream>
using namespace std;

Board::Board()
{
	width = 12;
	height = 19;
}
Board::~Board()
{
	width = 0;
	height = 0;
}
Board::Board(int x, int y)
{
	this->width = x;
	this->height = y;
}
void Board::print_board()
{
	showConsoleCursor(false);
	int a = 50, b = 70, c = 50, d = 70; // a = x1, c = y1, b = x2, d = y2
	for (int i = 0; i < width; i++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		a += 20;
		b += 20;
	}

	for (int j = 0; j < height; j++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		c += 20;
		d += 20;
	}

	for (int k = 0; k < width; k++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		a -= 20;
		b -= 20;
	}

	for (int i = 0; i < height; i++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		c -= 20;
		d -= 20;
	}
}

Piece::Piece()
{
	x = 0;
	y = 20;
	rotation = 0;
}
int Piece::get_x() {
	return x;
}
int Piece::get_y() {
	return y;
}
int Piece::get_rotation() {
	return rotation;
}
void Piece::set(int x, int y, int rotation) {
	this->x = x;
	this->y = y;
	this->rotation = rotation;
}

void Piece_L::print() {
	while (1) {
		if (rotation == 0) {
			int a1 = 170, b1 = 190;
			if (y > 320) {
				y -= 5;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

				y += 5;

				cls();

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
		if (rotation == 1) {
			if (x < -80) {
				x += 20;
			}
			int a1 = 150, b1 = 170;
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);

				y += 5;
				cls();

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 2) {
			int a1 = 150, b1 = 170;
			if (y > 320) {
				y -= 20;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

				y += 5;

				cls();

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 100) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
		if (rotation == 3) {
			if (x > 80) {
				x -= 20;
			}
			int a1 = 150, b1 = 170;
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);

				y += 5;

				cls();

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
	}
}
void Piece_S::print()
{
	int a1 = 170, b1 = 190;
	if (rotation > 1) {
		rotation = 0;
	}

	while (1) {
		if (rotation == 0) {
			if (x < -80) {
				x += 20;
			}
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 1) {
			if (y > 320) {
				y -= 20;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
				drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
	}
}
void Piece_Z::print() {
	if (rotation > 1) {
		rotation = 0;
	}
	int a1 = 170, b1 = 190;
	while (1) {
		if (rotation == 0) {
			if (x > 60) {
				x -= 20;
			}
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 60) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 1) {
			if (y > 320) {
				y -= 20;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
	}
}
void Piece_O::print()
{
	int a1 = 170, b1 = 190;
	while (y <= 340) {
		Board::print_board();
		drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
		drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
		drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
		drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);
		y += 5;
		cls();
		if (GetAsyncKeyState(VK_DOWN) != 0)
		{
			if (y != 340) {
				y += 5;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) != 0) {
			if (x != 80) {
				x += 20;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) != 0) {
			if (x != -100) {
				x -= 20;
			}
		}
		if (y == 340) {
			Board::print_board();
			drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);
			break;
		}
	}
}
void Piece_I::print() {
	if (rotation > 1) {
		rotation = 0;
	}
	int a1 = 130, b1 = 150;
	while (1) {
		if (rotation == 0) {
			if (x > 80) {
				x -= 60;
			}
			while (y <= 360) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 360) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -60) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 360) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					break;
				}
			}
		}
		if (y >= 360) {
			break;
		}
		if (rotation == 1) {
			if (y >= 300) {
				y -= 60;
			}
			while (y < 300) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
				drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 300) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 140) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -60) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 300) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);
					break;
				}
			}
		}
		if (y >= 300) {
			break;
		}
	}
}
void Piece_J::print() {
	int a1 = 170, b1 = 190;
	while (1) {
		if (rotation == 0) {
			if (x < -80) {
				x += 20;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 100) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
		if (rotation == 1) {
			if (x > 60) {
				x -= 40;
			}
			while (y <= 340)
			{
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 60) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 2) {
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
		if (rotation == 3) {
			if (x > 60) {
				x -= 20;
			}
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
				y += 5;
				cls();
				if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 60) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
	}
}
void Piece_T::print()
{
	int a1 = 150, b1 = 170;
	while (1) {
		if (rotation == 0) {
			if (x > 80) {
				x -= 40;
			}
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				y += 5;
				cls();

				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 1) {
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				y += 5;
				cls();

				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 100) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
		if (rotation == 2) {
			if (x > 80) {
				x -= 20;
			}
			while (y <= 340) {
				Board::print_board();
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				y += 5;
				cls();

				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					break;
				}
				if (y == 340) {
					Board::print_board();
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					break;
				}
			}
		}
		if (y >= 340) {
			break;
		}
		if (rotation == 3) {
			if (x < -60) {
				x += 20;
			}
			while (y <= 320) {
				Board::print_board();
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
				drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
				y += 5;
				cls();

				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 120) {
						x += 20;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						y += 5;
					}
				}
				if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -60) {
						x -= 20;
					}
				}
				if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					break;
				}
				if (y == 320) {
					Board::print_board();
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					break;
				}
			}
		}
		if (y >= 320) {
			break;
		}
	}
}