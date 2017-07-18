#pragma once

enum Direction { LEFT = 0, UP, RIGHT, DOWN };

enum Part { Head=0, Pants, NUM_PARTS };

enum Color { Blue=0, Purple, Brown, Green, NUM_COLORS };

struct Mark {
	Part part;
	Color color;
};

class Piece {
	int id;
	Mark marks[4];
	int rotation;
public:
	bool used;

	Piece();
	void init(int id, Mark left, Mark up, Mark right, Mark down);

	int getId();
	int getRotation();

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

void initPieces(Piece pieces[16]);
