#ifndef ADJLIST_C
#define ADJLIST_C

#include "adjlist.h"

AdjList* NewAdjList(int n_adjvertices) {
	AdjList *new = NULL;

	/* alloc acording to the number of adjacent vertices */
	new = calloc(n_adjvertices, sizeof(AdjList));

	return new;
} /*NewAdjList*/

AdjList* InsertAdjList(AdjList *adj, int current_position, int data, int value) {
	adj[current_position].index = data;
	adj[current_position].capacity = value;
	
	return adj;
} /*InsertAdjList*/

int SearchCapacityAdjList(AdjList *adj, int n_adjvertices, int data) {
	int current_vertice = 0, capacity = 0;

	for(current_vertice = 0; current_vertice < n_adjvertices; current_vertice++) 
		if(adj[current_vertice].index == data) {
			capacity = adj[current_vertice].capacity;
			break;
		}

	return capacity;
} /*SearchCapacityAdjList*/

void SearchPositionAdjList(AdjList *adj, int n_adjvertices, int data, int *position) {
	int current_vertice = 0;

	for(current_vertice = 0; current_vertice < n_adjvertices; current_vertice++) 
		if(adj[current_vertice].index == data) {
			*position = current_vertice;
			break;
		}
} /*SearchPositionAdjList*/

void ReallocAdjList(AdjList **adj, int size) {
	*adj = realloc(*adj, size*sizeof(AdjList));
} /*ReallocAdjList*/

void FreeAdjList(AdjList *adj) {
	if(adj == NULL)
		return;

	free(adj);
} /*FreeAdjList*/

#endif	//ADJLIST_C