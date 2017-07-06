#pragma once

class Piece;

struct List {
	Piece *head;
	Piece *tail;
};

void remove(List *list, Piece *piece);

void insert(List *list, Piece *piece, Piece *place);

void push(List *list, Piece *piece);

Piece *pop(List *list);

void printList(List *list);
