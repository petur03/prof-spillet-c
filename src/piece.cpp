
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "piece.h"
#include "list.h"

List *makePieces() {
	Piece *first = init(0, { Pants, Purple }, { Head, Green }, { Head, Brown }, { Pants, Brown }, NULL);
	Piece *next = first;
	Piece *prev;

	next = init(1, { Head, Purple }, { Pants, Green }, { Pants, Blue }, { Head, Brown }, (prev = next));
	next = init(2, { Head, Blue }, { Pants, Blue }, { Pants, Brown }, { Head, Brown }, (prev = next));
	next = init(3, { Head, Blue }, { Head, Brown }, { Pants, Green }, { Pants, Purple }, (prev = next));

	next = init(4, { Head, Purple }, { Pants, Brown }, { Pants, Green }, { Head, Blue }, (prev = next));
	next = init(5, { Pants, Purple }, { Head, Green }, { Head, Blue }, { Pants, Brown }, (prev = next));
	next = init(6, { Head, Purple }, { Pants, Blue }, { Pants, Green }, { Head, Brown }, (prev = next));
	next = init(7, { Head, Blue }, { Pants, Brown }, { Pants, Purple }, { Head, Brown }, (prev = next));

	next = init(8, { Pants, Green }, { Pants, Green }, { Head, Brown }, { Head, Purple }, (prev = next));
	next = init(9, { Pants, Green }, { Pants, Blue }, { Head, Green }, { Head, Purple }, (prev = next));
	next = init(10, { Head, Brown }, { Head, Blue }, { Pants, Green }, { Pants, Purple }, (prev = next));
	next = init(11, { Pants, Blue }, { Head, Green }, { Head, Green }, { Pants, Brown }, (prev = next));

	next = init(12, { Pants, Brown }, { Head, Purple }, { Head, Blue }, { Pants, Green }, (prev = next));
	next = init(13, { Pants, Blue }, { Head, Purple }, { Head, Green }, { Pants, Brown }, (prev = next));
	next = init(14, { Head, Purple }, { Pants, Brown }, { Pants, Green }, { Head, Green }, (prev = next));
	next = init(15, { Pants, Purple }, { Head, Green }, { Head, Blue }, { Pants, Brown }, (prev = next));

	List *list = (List*)calloc(1, sizeof(List));
	list->head = first;
	list->tail = next;
	return list;
}

Piece *init(int id, Mark left, Mark up, Mark right, Mark down, Piece *prev) {
	Piece *p = (Piece *)calloc(1, sizeof(Piece));
	p->id = id;
	p->marks[LEFT] = left;
	p->marks[UP] = up;
	p->marks[RIGHT] = right;
	p->marks[DOWN] = down;
	p->rotation = 0;
	if (prev != NULL)
		prev->next = p;
	p->next = NULL;
	p->prev = prev;

	return p;
}

Mark left(Piece *p) {
	return p->marks[(LEFT + p->rotation) % 4];
}

Mark up(Piece *p) {
	return p->marks[(UP + p->rotation) % 4];
}

Mark right(Piece *p) {
	return p->marks[(RIGHT + p->rotation) % 4];
}

Mark down(Piece *p) {
	return p->marks[(DOWN + p->rotation) % 4];
}

void rotate(Piece *p) {
	p->rotation = (p->rotation + 3) % 4; // Plus 3 to rotate in reverse direction
}

void printMark(Mark mark) {
	printf("%s,", mark.part == Pants ? "Pants" : "Head");
	switch (mark.color) {
	case Brown:
		printf("Brown\n");
		break;
	case Purple:
		printf("Purple\n");
		break;
	case Green:
		printf("Green\n");
		break;
	case Blue:
		printf("Blue\n");
		break;
	}


}

void checkMarks(Piece *piece) {
	assert(piece->marks[0].part == Pants || piece->marks[0].part == Head);
	assert(piece->marks[1].part == Pants || piece->marks[1].part == Head);
	assert(piece->marks[2].part == Pants || piece->marks[2].part == Head);
	assert(piece->marks[3].part == Pants || piece->marks[3].part == Head);
	assert(piece->marks[0].color == Brown || piece->marks[0].color == Purple || piece->marks[0].color == Green || piece->marks[0].color == Blue);
	assert(piece->marks[1].color == Brown || piece->marks[1].color == Purple || piece->marks[1].color == Green || piece->marks[1].color == Blue);
	assert(piece->marks[2].color == Brown || piece->marks[2].color == Purple || piece->marks[2].color == Green || piece->marks[2].color == Blue);
	assert(piece->marks[3].color == Brown || piece->marks[3].color == Purple || piece->marks[3].color == Green || piece->marks[3].color == Blue);
}

void checkRotation(Piece *piece) {
	assert(left(piece).part == Pants || left(piece).part == Head);
	assert(up(piece).part == Pants || up(piece).part == Head);
	assert(right(piece).part == Pants || right(piece).part == Head);
	assert(down(piece).part == Pants || down(piece).part == Head);
	assert(left(piece).color == Brown || left(piece).color == Purple || left(piece).color == Green || left(piece).color == Blue);
	assert(up(piece).color == Brown || up(piece).color == Purple || up(piece).color == Green || up(piece).color == Blue);
	assert(right(piece).color == Brown || right(piece).color == Purple || right(piece).color == Green || right(piece).color == Blue);
	assert(down(piece).color == Brown || down(piece).color == Purple || down(piece).color == Green || down(piece).color == Blue);
}

void checkPiece(Piece *piece) {
	assert(piece->id >= 0);
	assert(piece->id < 16);
	assert(piece->rotation >= 0);
	assert(piece->rotation < 4);
	checkMarks(piece);

	int oldRotation = piece->rotation;

	checkRotation(piece);
	rotate(piece);
	checkRotation(piece);
	rotate(piece);
	checkRotation(piece);
	rotate(piece);
	checkRotation(piece);
	rotate(piece);
	assert(oldRotation == piece->rotation);
}

void printPiece(Piece *piece) {
	if (piece->id < 0 || piece->id > 15) {
		printf("Piece error! id=%i\n");
	}
	printf("Piece %i\n", piece->id);

	printf("Left: ");
	printMark(piece->marks[LEFT]);
	printf("UP: ");
	printMark(piece->marks[UP]);
	printf("Right: ");
	printMark(piece->marks[RIGHT]);
	printf("Down: ");
	printMark(piece->marks[DOWN]);


}