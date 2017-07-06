
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "piece.h"

void remove(List *list, Piece *piece) {
	if (piece == list->head) {
		if (list->head->next == NULL) {
			list->head = NULL;
			list->tail = NULL;
		}
		else {
			list->head = list->head->next;
			list->head->prev = NULL;
		}
	}
	else if (piece == list->tail) {
		list->tail->prev->next = NULL;
		list->tail = list->tail->prev;
	} 
	else {
		piece->prev->next = piece->next;
		piece->next->prev = piece->prev;
	}
}

void insert(List *list, Piece *piece, Piece *place) {
	if (list->head == NULL) {
		piece->prev = NULL;
		piece->next = NULL;
		list->head = piece;
		list->tail = piece;
	}
	else if (place == list->tail) {
		piece->prev = place;
		piece->next = NULL;
		place->next = piece;
		list->tail = piece;
	}
	else if (place == NULL) {
		piece->next = list->head;
		piece->prev = NULL;
		list->head->prev = piece;
		list->head = piece;
	}
	else {
		Piece *next = place->next;
		piece->prev = place;
		piece->next = next;
		place->next = piece;
		next->prev = piece;
	}
}

void push(List *list, Piece *piece) {
	insert(list, piece, list->tail);
}

Piece *pop(List *list) {
	Piece *p = list->tail;
	remove(list, p);
	return p;
}

void printList(List *list) {
	Piece *current = list->head;
	while (current != NULL) {
		printf(" - ");
		current->print();
		current = current->next;
	}
	printf("\n");
}
