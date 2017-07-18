#pragma once

#include "piece.h"

struct Configuration {
	int piece;
	int rotation;
};

bool check(Piece *board[], int top, Piece *piece);

void printBoard(Piece *board[], int top);
