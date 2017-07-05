#pragma once

enum Direction { LEFT = 0, UP, RIGHT, DOWN };

enum Part { Head=0, Pants };

enum Color { Blue=0, Purple, Brown, Green };

typedef struct Mark_s {
	Part part;
	Color color;
} Mark;

typedef struct Piece_s {
	int id;
	Mark marks[4];
	int rotation;
	struct Piece_s *next;
	struct Piece_s *prev;
} Piece;

Piece *init(int id, Mark left, Mark up, Mark right, Mark down, Piece *prev);

Mark left(Piece *p);
Mark up(Piece *p);
Mark right(Piece *p);
Mark down(Piece *p);

void rotate(Piece *p);

List *makePieces();

void printPiece(Piece *piece);

void checkPiece(Piece *piece);
