#include <stdio.h>
#include <chrono>
#include "piece.h"
#include "board.h"
#include "list.h"

#define NUM_PIECES 16

void place(Piece *board[], int top, List *list);

int num_solutions = 0;
Piece *p15;

int main(int argc, const char** argv) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	List *list= makePieces();
	Piece *current = list->head;

	Piece *board[16];
	int top = 0;

	// piece 5 and 15 are equal. This is done to avoid duplicate solutions.
	p15 = list->tail;
	pop(list);

	//current = list->head;
	//while (current != NULL) {
	//	current->checkPiece();
	//	current->printPiece();
	//	current = current->next;
	//}

	place(board, 0, list);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	printf("Time difference = %f\n", (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0f);

	//getc(stdin);
	return 0;
}

void place(Piece *board[], int top, List *list) {
	if (list->head == NULL) {
		// DONE
		printf("Done! %i\n", num_solutions);
		printBoard(board, top);
		printf("\n");
		num_solutions++;
		//getc(stdin);
		return;
	}
	Piece *first = list->head;
	Piece *current = first;

	while (current != NULL) {

		if (top == 3 || top == 12 || top == 15) { // Avoid rotation duplicates
			if (current->getId() < board[0]->getId()) {
				current = current->next;
				continue;
			}
			if (current->getId() == 15 && // Avoid duplicate piece duplicates
				(top == 15 ||
				(top > 4 && board[3]->getId() == 5) ||
					(top > 13 && board[12]->getId() == 5)
					)) {
				current = current->next;
				continue;
			}
		}

		for (int i = 0; i < 4; i++) { // for each rotation
			if (check(board, top, current)) {
				Piece *prev = current->prev;
				remove(list, current);

				board[top] = current;

				if (current->getId() == 5) {
					push(list, p15);
				}
				place(board, top+1, list);
				if (current->getId() == 5) {
					pop(list);
				}

				insert(list, current, prev);

			}

			current->rotate();
		}

		current = current->next;
	}
}
