//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Graph.h"
#include"List.h"


int order;
int size;

typedef struct GraphObj {
	List* neighbors;
	char* color;
	int* parent;
	int* discover;
	int* finish;
} Graphobj;

// returns a Graph pointing to a 
//newly created GraphObj representing 
//a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(Graphobj));
	assert(G!=NULL);
	
	G->neighbors = calloc(n+1, sizeof(List*));
 	G->color = calloc(n+1, sizeof(char*));
 	G->parent = calloc(n+1,sizeof(int*));
 	G->discover = calloc(n+1,sizeof(int*));
 	G->finish = calloc(n+1,sizeof(int*));
	
	for(int i=1; i<=n; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->neighbors[i] = newList();
	}

	order = n;
	size = 0;
	
	return G;
}


int getOrder(Graph G) {
	if(G!=NULL) {
		return order;
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}

int getSize(Graph G) {
	if(G!=NULL) {
		return size;
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}



//return the parent of vertex u in 
//the Breadth- First tree created by 
//BFS(), or NIL if BFS() has not yet been called
//Pre: 1 <= u <= getOrder(G) 
int getParent(Graph G, int u) {
	if(G != NULL) {
		if( u >= 1 && u <= getOrder(G) ) {
			return G->parent[u];
		}
		else if(u < 1) {
			printf("PreCondition Error: getParent: vertex u is too low \n");
			exit(1);
		}
		else {
			printf("PreCondition Error: getParent: vertex u is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}








//inserts a new edge joining u to v, 
//i.e. u is added to the adjacency List of v, 
//and v to the adjacency List of u.
//Pre: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
	if( G != NULL ) {
		if( 1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G) ) {
			addArc(G,u,v);
			addArc(G,v,u);
			size--;
		}
		else if (1 > u) {
			printf("PreCondition Error: addEdge: vertex u is too low \n");
			exit(1);
		}
		else if(1 > v) {
			printf("PreCondition Error: addEdge: vertex v is too low \n");
			exit(1);
		}
		else if(u > getOrder(G)) {
			printf("PreCondition Error: addEdge: vertex u is too high \n");
			exit(1);
		}
		else { // v > getOrder(G)
		printf("PreCondition Error: addEdge: vertex v is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
	
}



//inserts a new directed edge from u to v, 
//i.e. v is added to the adjacency List of u 
//(but not u to the adjacency List of v)
//Pre: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
	if( G != NULL ) {
		if( 1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G) ) {
			if(length(G->neighbors[u]) == 0 ) {
				append(G->neighbors[u],v);
			}
			else {
				int len = length(G->neighbors[u])-1;
				moveFront(G->neighbors[u]);
				while( len > 0 && get(G->neighbors[u]) < v ) {
					moveNext(G->neighbors[u]);
					len--;
				}
				if( get(G->neighbors[u]) > v) {
 					insertBefore(G->neighbors[u],v);
 				}
 				else {
 					insertAfter(G->neighbors[u],v);
 				}
			}
			size++;
		}
		else if (1 > u) {
			printf("PreCondition Error: addArc: vertex u is too low \n");
			exit(1);
		}
		else if(1 > v) {
			printf("PreCondition Error: addArc: vertex v is too low \n");
			exit(1);
		}
		else if(u > getOrder(G)) {
			printf("PreCondition Error: addArc: vertex u is too high \n");
			exit(1);
		}
		else { // v > getOrder(G)
		printf("PreCondition Error: addArc: vertex v is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}








//deletes all edges of G, 
//restoring it to its original
//(no edge) state.
void makeNull(Graph G) {
	if(G != NULL) {
		size = 0;
		for(int i=1; i<= getOrder(G); i++) {
			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->discover[i] = UNDEF;
			G->finish[i] = UNDEF;
			freeList(&G->neighbors[i]);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}


//freeGraph() frees all dynamic 
//memory associated with the Graph 
//*pG,then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
	if(*pG != NULL && pG != NULL) {
		makeNull(*pG);
		free((*pG)->discover);
		free((*pG)->finish);
 		free((*pG)->parent);
 		free((*pG)->color);
		free((*pG)->neighbors);
	}
	free(*pG);
	*pG = NULL;
}





//prints the adjacency list representation
// of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	if ( G != NULL ) {
		for(int i=1; i<= getOrder(G) ; i++) {
			fprintf(out, "%d", i);
			fprintf(out, "%s", ":");
			printList(out, G->neighbors[i]);
			fprintf(out, "%s", "\n");
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}




 /* Pre: 1<=u<=n=getOrder(G) */ 
int getDiscover(Graph G, int u) {
	if(G != NULL) {
		if( u >= 1 && u <= getOrder(G) ) {
			return G->discover[u];
		}
		else if(u < 1) {
			printf("PreCondition Error: getDiscover: vertex u is too low \n");
			exit(1);
		}
		else {
			printf("PreCondition Error: getDiscover: vertex u is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}




/* Pre: 1<=u<=n=getOrder(G) */ 
int getFinish(Graph G, int u) {
	if(G != NULL) {
		if( u >= 1 && u <= getOrder(G) ) {
			return G->finish[u];
		}
		else if(u < 1) {
			printf("PreCondition Error: getFinish: vertex u is too low \n");
			exit(1);
		}
		else {
			printf("PreCondition Error: getFinish: vertex u is too high \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}


void visit(Graph G, List L, int x ,int* time) {
	if(G != NULL) {
		G->color[x] = 'g';
		++(*time);
		G->discover[x] = *time;
		if(length(G->neighbors[x])>0) {
			moveFront(G->neighbors[x]);
			for(int z=1; z<= length(G->neighbors[x]); z++) {
				int y = get(G->neighbors[x]);
				if( G->color[y]=='w') {
					G->parent[y] = x;
					visit(G, L, y,time);
				}
				moveNext(G->neighbors[x]);
			}
		}
		G->color[x] = 'b';
		++(*time);
		G->finish[x] = *time;
		prepend(L,x);
	}
}


/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S) {
	if(G != NULL) {
		if( length(S)==getOrder(G) ) {
			for(int i=1; i<=getOrder(G); i++) {
				G->color[i] = 'w';
				G->parent[i] = NIL;
				G->discover[i] = UNDEF;
				G->finish[i] = UNDEF;
			}
			int t = 0;
			if( length(S) > 0 ) {
				moveFront(S);
				for(int i=1; i<= getOrder(G); i++) {
					int x = get(S);
					moveNext(S);
					if(G->color[x]=='w') {
						G->parent[x] = 0;
						visit(G, S, x, &t);
					}
				}
				for(int i=1; i<= getOrder(G); i++) {
					deleteBack(S);
				}
			}
			
		}
		else {
			printf("PreCondition Error: DFS: Length of List doesn't equal length of G \n");
			exit(1);
		}
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}





Graph copyGraph(Graph G) {
	if ( G != NULL) {
		Graph NG = newGraph(getOrder(G));
		makeNull(NG);
		order = getOrder(G);
		size = getSize(G);	
		for(int i=1; i<=getOrder(G); i++) {
			NG->color[i] = G->color[i];
			NG->parent[i] = G->parent[i];
			NG->discover[i] = G->discover[i];
			NG->finish[i] = G->finish[i];
			NG->neighbors[i] = copyList(G->neighbors[i]);
		}
		return NG;
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}




Graph transpose(Graph G) {
	if ( G != NULL) {
		Graph NG = newGraph(getOrder(G));
		order = getOrder(G);
		size = getSize(G);	
		for(int i=1; i<=getOrder(G); i++) {
			if( length(G->neighbors[i])!=0) {
				moveFront(G->neighbors[i]);
				int l = length(G->neighbors[i]);
				while ( l > 0  ) {
				int j = get(G->neighbors[i]);;
					if(length(NG->neighbors[j]) == 0) {
						append(NG->neighbors[j], i);
					}
					else {
						moveFront(NG->neighbors[j]);
						while(index(NG->neighbors[j]) != -1 && get(NG->neighbors[j]) < i ) {
							moveNext(NG->neighbors[j]);
						}
						if(index(NG->neighbors[j]) == -1) {
							append(NG->neighbors[j], i);
						}
						else {
							insertBefore(NG->neighbors[j], i);
						}
					}
					l--;
					moveNext(G->neighbors[i]);
				}
			}	
		}
		return NG;
	}
	else {
		printf("Graph Error: Graph is NULL \n");
		exit(1);
	}
}













