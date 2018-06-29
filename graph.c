#ifndef GRAPH_C
#define GRAPH_C

#include "adjlist.h"
#include "graph.h"

Graph* NewGraph(int n_vertices) {
	Graph *new = NULL;

	/* alloc acording to the number of vertices in the graph */
	new = calloc(n_vertices, sizeof(Graph));

	return new;
} /*NewGraph*/

Graph* ReadInput(int *n_vertices, int *source, int *sink) {
	Graph *graph = NULL;
	/* variables declared in the problem's especification */
	int V = 0, E = 0, F = 0, C = 0, u = 0, v = 0, m = 0, f = 0, c = 0;
	/* auxiliar variables */
	int local_n_vertices = 0, local_source = 0, local_sink = 0, current_vertice = 0, current_edge = 0;

	/* take first information to compose the graph */
	scanf("%d", &V);
	scanf("%d", &E);
	scanf("%d", &F);
	scanf("%d", &C);

	local_n_vertices = V + 2;
	local_source = local_n_vertices - 2;
	local_sink = local_n_vertices - 1;

	/* auxiliar array to store the position of insertion in the adjacency list */
	int current_position[local_n_vertices];

	for(current_vertice = 0; current_vertice < local_n_vertices; current_vertice++)
		current_position[current_vertice] = 0;

	/* create the graph */
	graph = NewGraph(local_n_vertices);

	/* insert edges ont the graph */
	for(current_edge = 0; current_edge < E; current_edge++) {
		scanf("%d", &u);
		scanf("%d", &v);
		scanf("%d", &m);

		/* set the real edge */
		graph[u].n_adjvertices++;
		graph = BuildGraph(graph, current_position[u], u, v, m);
		current_position[u]++;

		/* set the reverse edge */
		graph[v].n_adjvertices++;
		graph = BuildGraph(graph, current_position[v], v, u, 0);
		current_position[v]++;
	}

	/* start building the source vertice */
	graph[local_source].n_adjvertices = F;
	graph[local_source].adjnodes = NewAdjList(graph[local_source].n_adjvertices);

	/* add edges to the source vertice */
	for(current_vertice = 0; current_vertice < F; current_vertice++) {
		scanf("%d", &f);

		/* set the real edge to the source */
		graph[local_source].adjnodes = InsertAdjList(graph[local_source].adjnodes, current_position[local_source], f, INT_MAX);
		current_position[local_source]++;

		/* set the reverse edge */
		graph[f].n_adjvertices++;
		graph = BuildGraph(graph, current_position[f], f, local_source, 0);
		current_position[f]++;
	}

	/* prepare the sink vertice */
	graph[local_sink].n_adjvertices = C;
	graph[local_sink].adjnodes = NewAdjList(graph[local_sink].n_adjvertices);

	/* take real edges */
	for(current_vertice = 0; current_vertice < C; current_vertice++){
		scanf("%d", &c);
		
		/* set the real edge from c to the sink */
		graph[c].n_adjvertices++;
		graph = BuildGraph(graph, current_position[c], c, local_sink, INT_MAX);
		current_position[c]++;

		/* set the reverse edges */
		graph[local_sink].adjnodes = InsertAdjList(graph[local_sink].adjnodes, current_position[local_sink], c, 0);
		current_position[local_sink]++;

	}

	/* store important information in pointer for future use */
	*n_vertices = local_n_vertices;
	*source = local_source;
	*sink = local_sink;

	return graph;
} /*ReadInput*/

Graph* BuildGraph(Graph *graph, int current_position, int from, int to, int capacity) {
	/* insert new node on adjacency list */
	if(graph[from].adjnodes == NULL) {
		graph[from].adjnodes = NewAdjList(graph[from].n_adjvertices);
		graph[from].adjnodes = InsertAdjList(graph[from].adjnodes, current_position, to, capacity);
	}
	/* change the memory size to insert a new node */
	else {
		ReallocAdjList(&graph[from].adjnodes, graph[from].n_adjvertices);
		graph[from].adjnodes = InsertAdjList(graph[from].adjnodes, current_position, to, capacity);
	}

	return graph;
} /*BuildGraph*/

bool BFS(Graph *graph, int parent[], int n_vertices, int source, int sink) {
	int queue[n_vertices], front = -1, rear = -1, current_vertice = 0, atual_vertice = 0, next_vertice = 0;
	bool visited[n_vertices];

	/* initialize array and queue */
	for(current_vertice = 0; current_vertice < n_vertices; current_vertice++) {
		queue[current_vertice] = -1;
		visited[current_vertice] = false; 
	}
		
	/* start BFS from source */
	visited[source] = true;
	parent[source] = -1;
	front = 0;
	rear++;
	queue[rear] = source;

	/* execute the search */
	while(front <= rear && atual_vertice != sink) {
		atual_vertice = queue[front];
		front++;

		for(current_vertice = 0; current_vertice < graph[atual_vertice].n_adjvertices; current_vertice++) {
			next_vertice = graph(atual_vertice, current_vertice).index;

			if((visited[next_vertice] == false) && (graph(atual_vertice, current_vertice).capacity > 0)) {
				visited[next_vertice] = true;
				parent[next_vertice] = atual_vertice;
				rear++;
				queue[rear] = next_vertice;
			}
		}
	}

	return (visited[sink] == true);
} /*BFS*/

int FindMinimumCapacity(Graph *graph, int parent[], int n_vertices, int source, int sink) {
	int current_flow = INT_MAX, current_vertice = sink, father = 0;

	for(current_vertice = sink; parent[current_vertice] != source; current_vertice = parent[current_vertice]) {
		father = parent[current_vertice];	

		/* search the capacity of the father - current_vertice edge */	
		if(current_flow >  SearchCapacityAdjList(graph[father].adjnodes, n_vertices, current_vertice)) 
			current_flow =  SearchCapacityAdjList(graph[father].adjnodes, n_vertices, current_vertice);
	}
	return current_flow;

} /*FindMinimumCapacity*/

Graph* UpdateCapacity(Graph *graph, int parent[], int n_vertices, int current_flow, int source, int sink) {
	int current_vertice = 0, father = 0, position1 = 0, position2 = 0;

	for(current_vertice = sink; parent[current_vertice] != source; current_vertice = parent[current_vertice]) {
		father = parent[current_vertice];

		/* search the position of the current_vertice on the father list (normal direction) */
		SearchPositionAdjList(graph[father].adjnodes, n_vertices, current_vertice, &position1);
		/* search the position of the father on the current_vertice list (reverse direction) */
		SearchPositionAdjList(graph[current_vertice].adjnodes, n_vertices, father, &position2);

		graph(father, position1).capacity -= current_flow;
		graph(current_vertice, position2).capacity += current_flow;
	}

	return graph;
} /*UpdateCapacity*/

int MaximumFlow(Graph *graph, int n_vertices, int source, int sink) {
 	int max_flow = 0, current_flow = 0, parent[n_vertices];
 	int current_vertice = 0;

 	for(current_vertice = 0; current_vertice < n_vertices; current_vertice++)
 		parent[current_vertice] = -1;

 	/* algorithm's execution */
 	/* BFS finds an augmenting path*/
 	while(BFS(graph, parent, n_vertices, source, sink)) {
 		/* find the minimum capacity of the path */
 		current_flow = FindMinimumCapacity(graph, parent, n_vertices, source, sink);
 		/* update the residual capacity of each edge */
 		graph = UpdateCapacity(graph, parent, n_vertices, current_flow, source, sink);
 		/* augment the total flow in the graph*/
 		max_flow += current_flow;		
 	}

  	return max_flow;
} /*MaximumFlow*/

void FreeGraph(Graph *graph, int n_vertices) {
	int current_vertice = 0;

	for(current_vertice = 0; current_vertice < n_vertices; current_vertice++)
		FreeAdjList(graph[current_vertice].adjnodes);
	free(graph);
} /*FreeGraph*/

#endif	//GRAPH_C
