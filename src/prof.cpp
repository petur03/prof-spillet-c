#include <stdio.h>
#include "piece.h"
#include "board.h"
#include "list.h"

#define NUM_PIECES 16

void place(Piece *board[], int top, List *list, Piece *piece);

int num_solutions = 0;
Piece *p15;

int main(int argc, const char** argv) {
	List *list= makePieces();
	Piece *current = list->head;
	Piece *last;

	Piece *board[16];
	int top = 0;

	// piece 5 and 15 are equal. This is done to avoid duplicate solutions.
	p15 = list->tail;
	pop(list);

	current = list->head;
	while (current != NULL) {
		checkPiece(current);
		printPiece(current);
		current = current->next;
	}


	//getc(stdin);
	//return 0;

	place(board, 0, list, list->head);

	printf("Hello world!\n");
	getc(stdin);
	return 0;
}

void place(Piece *board[], int top, List *list) {
	//printf("Place.. top = %i\n", top);
	//printBoard(board, top);
	if (piece == NULL) {
		// DONE
		printf("Done! %i\n", num_solutions);
		printBoard(board, top);
		printf("\n");
		num_solutions++;
		getc(stdin);
		return;
	}
	Piece *first = piece;
	Piece *current = first;

	while (current != NULL) {
		//printf("Current:\n");
		//printPiece(current);
		// for each rotation
		for (int i = 0; i < 4; i++) {
			if (check(board, top, current)) {
				Piece *prev = current->prev;
				remove(list, current);

				board[top] = current;

				if (current->id == 5) {
					push(list, p15);
				}
				place(board, top+1, first, last);
				if (current->id == 5) {
					pop(list);
				}

				if (prev == NULL)
					first = current;
				else {
					prev->next->prev = current;
					prev->next = current;
				}

			}

			//printf("Rotating\n");
			rotate(current);
		}

		prev = current;
		current = current->next;
	}
}
