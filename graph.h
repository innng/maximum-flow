#ifndef GRAPH_H
#define GRAPH_H

#include <time.h>
#include <limits.h>
#include "adjlist.h"
/* easier way to acess the info in a node of the adjacency list */
#define graph(i, j) graph[i].adjnodes[j]

/* basic struct for a graph using adjacency list */
typedef struct TGraph {
	int n_adjvertices;
	AdjList *adjnodes;
}Graph;

/* allocs memory for the vertices, returns the pointer to the array of nodes */
Graph* NewGraph(int n_vertices);

/* recieves the input via stdin and start building the graph, returns pointer to the graph */
Graph* ReadInput(int *n_vertices, int *source, int *sink);

/* inserts edges on a adjacency list and realloc memory if its necessary, returns pointer to the struct */
Graph* BuildGraph(Graph *graph, int current_position, int from, int to, int capacity);

/* executes the BFS algorithm and returns if is possible to find a path from the source to the sink */
bool BFS(Graph *graph, int parent[], int n_vertices, int source, int sink);

/* based on the BFS execution, find the small capacity in a path from the source to the sink*/
int FindMinimumCapacity(Graph *graph, int parent[], int n_vertices, int source, int sink);

/* updates the flow on the graph and returns its pointer */
Graph* UpdateCapacity(Graph *graph, int parent[], int n_vertices, int current_flow, int source, int sink);

/* executes the Edmonds-Karp algorithm on the graph, return the maximum flow */
int MaximumFlow(Graph *graph, int n_vertices, int source, int sink);

/* free all memory allocated for a given graph */
void FreeGraph(Graph *graph, int n_vertices);

#endif	//GRAPH_H