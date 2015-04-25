
/*	strong.c
	Identify strongly connected components in a graph

	by: Steven Skiena
	begun: March 27, 2002
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved.

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/

#include "bool.h"
#include "graph.h"
#include "stack.h"

extern bool processed[];	/* which vertices have been processed */
extern bool discovered[];	/* which vertices have been found */
extern int parent[];		/* discovery relation */

extern int entry_time[];	/* time of vertex entry */
extern int exit_time[];		/* time of vertex exit */

int low[MAXV+1];		/* oldest vertex surely in component of v */
int scc[MAXV+1];		/* strong component number for each vertex */

stack active;			/* active vertices of unassigned component */
int components_found;		/* number of strong components identified */

process_vertex_early(int v)
{

	push(&active,v);
}
process_vertex_late(graph *g, int v)
{

	if (low[v] == v) { 		/* edge (parent[v],v) cuts off scc */
		pop_component(&g, v);
	}

	if (entry_time[low[v]] < entry_time[low[parent[v]]])
		low[parent[v]] = low[v];
}

pop_component(graph *g, int v)
{
        int t;                  /* vertex placeholder */

	components_found = components_found + 1;
	printf("%d is in component %d \n",v,components_found);
	scc[ v ] = components_found;
	while ((t = pop(&active)) != v) {
		scc[ t ] = components_found;
		printf("%d is in component %d with %d \n",t,components_found,v);
	}
}

process_edge(int x, int y)
{
	int class;		/* edge class */

	class = edge_classification(x,y);

	if (class == BACK) {
		if (entry_time[y] < entry_time[ low[x] ] )
			low[x] = y;
	}

	if (class == CROSS) {
		if (scc[y] == -1)	/* component not yet assigned */
			if (entry_time[y] < entry_time[ low[x] ] )
                        	low[x] = y;
	}
}





strong_components(graph *g)
{
	int i;				/* counter */

	for (i=1; i<=(g->nvertices); i++) {
		low[i] = i;
		scc[i] = -1;
	}

	components_found = 0;

	init_stack(&active);
	initialize_search(&g);

	for (i=1; i<=(g->nvertices); i++)
		if (discovered[i] == FALSE) {
			dfs(g,i);
			/*pop_component(i);*/
		}
}
int debug = 1;
source_sink_work(graph *g)
{
	int in[components_found+1];
	int out[components_found+1];
	int i;				/* counter */
	for(i=1;i<components_found+1;i++){
		in[i] = 0;
		out[i] = 0;
		if(debug){
		}
	}
	edgenode *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		p = g->edges[i];
		while (p != NULL) {
			int isIn = 0;
			if(scc[p->y] == scc[i]) isIn = 1;
		    if(scc[p->y] != scc[i]){
				in[scc[p->y]] = in[scc[p->y]] + 1;
				out[scc[i]] = out[scc[i]] + 1;
			}
			p = p->next;
		}
	}
	int base = 0;
	int sponge = 0;
	for(i=1;i<components_found+1;i++){
			if(in[i] == 0 && base == 0) base = i;
			else if(in[i] == 0 && base != 0) base = -1;
			if(out[i] == 0 && sponge == 0) sponge = i;
			else if(out[i] == 0 && sponge != 0) sponge = -1;
	
	}
	if(base > 0){
		int i;
		for(i = 1;i < MAXV+1;i++){
			if(scc[i] == base) printf("%d,",i);
		}	
			printf(" are in the base component\n");
	}
	else{
	  printf("there are no candidates for bases\n");
	}
	if(sponge > 0) {
		int i;
		for(i = 1;i < MAXV+1;i++){
			if(scc[i] == sponge) printf("%d,",i);
		}	
			printf(" are in the sponge component\n");
	}
	else{
	  printf("there are no candidates for sponges\n");
	}
}


main()
{
	graph g;
	int i;

	read_graph(&g,TRUE);
	print_graph(&g);

	strong_components(&g);

    source_sink_work(&g);	



}
