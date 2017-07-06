#pragma once

#include "list.h"

enum Direction { LEFT = 0, UP, RIGHT, DOWN };

enum Part { Head=0, Pants };

enum Color { Blue=0, Purple, Brown, Green };

struct Mark {
	Part part;
	Color color;
};

class Piece {
	int id;
	Mark marks[4];
	int rotation;
public:
	Piece *next;
	Piece *prev;

	Piece(int id, Mark left, Mark up, Mark right, Mark down, Piece *prev);

	int getId();

	Mark left();
	Mark up();
	Mark right();
	Mark down();

	void rotate();
	void printPiece();
	void print();

	void checkPiece();
	void checkMarks();
	void checkRotation();
};

List *makePieces();
