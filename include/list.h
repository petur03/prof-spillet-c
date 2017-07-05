#pragma once

#include "piece.h"

typedef struct List_s {
	Piece *head;
	Piece *tail;
} List;

void remove(List *list, Piece *piece);

void insert(List *list, Piece *piece, Piece *place);

void push(List *list, Piece *piece);

Piece *pop(List *list);
