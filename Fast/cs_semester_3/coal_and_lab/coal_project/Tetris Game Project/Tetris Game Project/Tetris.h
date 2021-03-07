#pragma once
#include <iostream>
using namespace std;
//
//class Tetris
//{
//public:
//	void Instructions();
//};

class Board
{
protected:
	int width;
	int height;
public:
	Board();
	Board(int, int);
	~Board();
	void print_board();
};

class Piece : public Board
{
protected:
	int x;
	int y;
	int rotation;
public:
	Piece();
	void set(int x, int y, int rotation);
	int get_x();
	int get_y();
	int get_rotation();

	void virtual print() = 0;
};

class Piece_L : public Piece
{
public:
	void print() override;
};
class Piece_S : public Piece
{
public:
	void print() override;
};
class Piece_Z : public Piece
{
public:
	void print() override;
};
class Piece_O : public Piece
{
public:
	void print() override;
};
class Piece_I : public Piece
{
public:
	void print() override;
};
class Piece_J : public Piece
{
public:
	void print() override;
};
class Piece_T : public Piece
{
public:
	void print() override;
};