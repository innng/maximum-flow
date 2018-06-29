#ifndef TP1_C
#define TP1_C

#include "adjlist.h"
#include "graph.h"

int main() {
	Graph *graph = NULL;
	int n_vertices = 0, source = 0, sink = 0, MaxFlow = 0;

	graph = ReadInput(&n_vertices, &source, &sink);
	MaxFlow = MaximumFlow(graph, n_vertices, source, sink);
	printf("%d\n", MaxFlow);

	FreeGraph(graph, n_vertices);
	return 0;
}

#endif	//TP1_C