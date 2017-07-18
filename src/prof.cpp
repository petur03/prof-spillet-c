#include <stdio.h>
#include <chrono>
#include <vector>
#include "piece.h"
#include "board.h"

#define NUM_PIECES 16

using namespace std;

void place(Piece *board[], int top, Piece pieces[16]);

int num_solutions = 0;

vector<Configuration*> solutions;

int main(int argc, const char** argv) {
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	Piece pieces[16];
	initPieces(pieces);

	Piece *board[16];
	int top = 0;

	// piece 5 and 15 are equal. This is done to avoid duplicate solutions.
	pieces[15].used = true;

	//for (int i = 0; i < 16; i++) {
	//	pieces[i].checkPiece();
	//	pieces[i].printPiece();
	//}

	place(board, 0, pieces);

	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	printf("Time difference = %f\n", (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0f);

	num_solutions = 0;
	for (vector<Configuration *>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
		Configuration *solution = *(it._Ptr);
		printf("Solution %i:\n", num_solutions);
		for (int i = 0; i < 16; i++) {
			printf("%d(%d) ", solution[i].piece, solution[i].rotation);
		}
		printf("\n");
		num_solutions++;


	}

	getc(stdin);
	return 0;
}

void place(Piece *board[], int top, Piece pieces[16]) {
	if (top == 16) {
		// DONE
		printf("Done! %i\n", num_solutions);
		printBoard(board, top);
		Configuration *solution = new Configuration[16];
		for (int i = 0; i < 16; i++) {
			solution[i].piece = board[i]->getId();
			solution[i].rotation = board[i]->getRotation();
		}
		solutions.push_back(solution);
		printf("\n");
		num_solutions++;

		//getc(stdin);
		return;
	}

	for (int i = 0; i < 16; i++) {
		Piece *current = &pieces[i];
		if (current->used) {
			continue;
		}

		if (top == 3 || top == 12 || top == 15) { // Avoid rotation duplicates
			if (current->getId() < board[0]->getId()) {
				continue;
			}
			if (current->getId() == 15 && // Avoid duplicate piece duplicates
				(top == 15 ||
				(top > 4 && board[3]->getId() == 5) ||
					(top > 13 && board[12]->getId() == 5)
					)) {
				continue;
			}
		}

		for (int i = 0; i < 4; i++) { // for each rotation
			if (check(board, top, current)) {
				current->used = true;

				board[top] = current;

				if (current->getId() == 5) {
					pieces[15].used = false;
				}

				place(board, top+1, pieces);

				if (current->getId() == 5) {
					pieces[15].used = true;
				}

				current->used = false;
			}

			current->rotate();
		}
	}
}
