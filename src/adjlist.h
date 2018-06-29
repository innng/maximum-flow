#ifndef ADJLIST_H
#define ADJLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* struct of an adjacency list using a dynamic allocated vector to a graph */
typedef struct TAdjList {
	int index;
	int capacity; 	
}AdjList;

/* alloc memory for the adjacency list, returns the pointer to the list */
AdjList* NewAdjList(int n_adjvertices);

/* insert an edge in the adjacency list (fill a position in the list), returns the pointer to the list*/
AdjList* InsertAdjList(AdjList *adj, int current_position, int data, int value);

/* search an node on the adjacency list and returns its capacity */
int SearchCapacityAdjList(AdjList *adj, int n_adjvertices, int data);

/* search a given node and return the postion on the adjacency list */
void SearchPositionAdjList(AdjList *adj, int n_adjvertices, int data, int *position);

/* change the size of the list once it was already allocated */
void ReallocAdjList(AdjList **adj, int size);

/* free all memory allocated for a given list */
void FreeAdjList(AdjList *adj);

#endif	//ADJLIST_H