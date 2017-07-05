
#include <stdlib.h>
#include "list.h"

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

}

void push(List *list, Piece *piece) {
	insert(list, piece, list->tail);
}

Piece *pop(List *list) {
	Piece *p = list->tail;
	remove(list, p);
	return p;
}
