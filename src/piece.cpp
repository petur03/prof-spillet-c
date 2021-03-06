
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "piece.h"

void initPieces(Piece pieces[16]) {
	pieces[0].init(0, { Pants, Purple }, { Head, Green }, { Head, Brown }, { Pants, Brown });
	pieces[1].init(1, { Head, Purple }, { Pants, Green }, { Pants, Blue }, { Head, Brown });
	pieces[2].init(2, { Head, Blue }, { Pants, Blue }, { Pants, Brown }, { Head, Brown });
	pieces[3].init(3, { Head, Blue }, { Head, Brown }, { Pants, Green }, { Pants, Purple });

	pieces[4].init(4, { Head, Purple }, { Pants, Brown }, { Pants, Green }, { Head, Blue });
	pieces[5].init(5, { Pants, Purple }, { Head, Green }, { Head, Blue }, { Pants, Brown });
	pieces[6].init(6, { Head, Purple }, { Pants, Blue }, { Pants, Green }, { Head, Brown });
	pieces[7].init(7, { Head, Blue }, { Pants, Brown }, { Pants, Purple }, { Head, Brown });

	pieces[8].init(8, { Pants, Green }, { Pants, Green }, { Head, Brown }, { Head, Purple });
	pieces[9].init(9, { Pants, Green }, { Pants, Blue }, { Head, Green }, { Head, Purple });
	pieces[10].init(10, { Head, Brown }, { Head, Blue }, { Pants, Green }, { Pants, Purple });
	pieces[11].init(11, { Pants, Blue }, { Head, Green }, { Head, Green }, { Pants, Brown });

	pieces[12].init(12, { Pants, Brown }, { Head, Purple }, { Head, Blue }, { Pants, Green });
	pieces[13].init(13, { Pants, Blue }, { Head, Purple }, { Head, Green }, { Pants, Brown });
	pieces[14].init(14, { Head, Purple }, { Pants, Brown }, { Pants, Green }, { Head, Green });
	pieces[15].init(15, { Pants, Purple }, { Head, Green }, { Head, Blue }, { Pants, Brown });

}

Piece::Piece() {
}

void Piece::init(int id, Mark left, Mark up, Mark right, Mark down) {
	this->id = id;
	this->marks[LEFT] = left;
	this->marks[UP] = up;
	this->marks[RIGHT] = right;
	this->marks[DOWN] = down;
	this->rotation = 0;
	this->used = false;
}

int Piece::getId() {
	return id;
}

Mark Piece::left() {
	return marks[(LEFT + rotation) % 4];
}

Mark Piece::up() {
	return marks[(UP + rotation) % 4];
}

Mark Piece::right() {
	return marks[(RIGHT + rotation) % 4];
}

Mark Piece::down() {
	return marks[(DOWN + rotation) % 4];
}

void Piece::rotate() {
	rotation = (rotation + 3) % 4; // Plus 3 to rotate in reverse direction
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

void Piece::checkMarks() {
	assert(marks[0].part == Pants || marks[0].part == Head);
	assert(marks[1].part == Pants || marks[1].part == Head);
	assert(marks[2].part == Pants || marks[2].part == Head);
	assert(marks[3].part == Pants || marks[3].part == Head);
	assert(marks[0].color == Brown || marks[0].color == Purple || marks[0].color == Green || marks[0].color == Blue);
	assert(marks[1].color == Brown || marks[1].color == Purple || marks[1].color == Green || marks[1].color == Blue);
	assert(marks[2].color == Brown || marks[2].color == Purple || marks[2].color == Green || marks[2].color == Blue);
	assert(marks[3].color == Brown || marks[3].color == Purple || marks[3].color == Green || marks[3].color == Blue);
}

void Piece::checkRotation() {
	assert(left().part == Pants || left().part == Head);
	assert(up().part == Pants || up().part == Head);
	assert(right().part == Pants || right().part == Head);
	assert(down().part == Pants || down().part == Head);
	assert(left().color == Brown || left().color == Purple || left().color == Green || left().color == Blue);
	assert(up().color == Brown || up().color == Purple || up().color == Green || up().color == Blue);
	assert(right().color == Brown || right().color == Purple || right().color == Green || right().color == Blue);
	assert(down().color == Brown || down().color == Purple || down().color == Green || down().color == Blue);
}

void Piece::checkPiece() {
	assert(id >= 0);
	assert(id < 16);
	assert(rotation >= 0);
	assert(rotation < 4);
	checkMarks();

	int oldRotation = rotation;

	checkRotation();
	rotate();
	checkRotation();
	rotate();
	checkRotation();
	rotate();
	checkRotation();
	rotate();
	assert(oldRotation == rotation);
}

void Piece::print() {
	printf("%i(%i) ", id, rotation);
}

void Piece::printPiece() {
	if (id < 0 || id > 15) {
		printf("Piece error! id=%i\n", id);
	}
	printf("Piece %i\n", id);

	printf("Left: ");
	printMark(marks[LEFT]);
	printf("UP: ");
	printMark(marks[UP]);
	printf("Right: ");
	printMark(marks[RIGHT]);
	printf("Down: ");
	printMark(marks[DOWN]);


}