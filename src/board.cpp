
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

bool match(Mark mark1, Mark mark2) {
	return (mark1.part != mark2.part) && (mark1.color == mark2.color);
}

bool matchLeft(Piece *board[], int top, Piece *piece) {
	return match(board[top - 1]->right(), piece->left());
}

bool matchUp(Piece *board[], int top, Piece *piece) {
	return match(board[top - 4]->down(), piece->up());
}

bool matchBoth(Piece *board[], int top, Piece *piece) {
	return matchLeft(board, top, piece) && matchUp(board, top, piece);
}

bool check(Piece *board[], int top, Piece *piece) {
	switch (top) {
	case 0:
		return true;
		break;
	case 1:
	case 2:
	case 3:
		return matchLeft(board, top, piece);
		break;
	case 4:
	case 8:
	case 12:
		return matchUp(board, top, piece);
		break;
	case 5:
	case 6:
	case 7:
	case 9:
	case 10:
	case 11:
	case 13:
	case 14:
	case 15:
		return matchBoth(board, top, piece);
		break;
	default:
		printf("Unknown index!! %i", top);
		exit(-1);
	}
}

void printBoard(Piece *board[], int top) {
	for (int i = 0; i < top; i++) {
		board[i]->print();
		if (((i+1) % 4) == 0)
			printf("\n");
	}
	printf("\n");
}
