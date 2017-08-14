//-----------------------------------------------------------------------------
// FindComponents.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d", &n);
	
	Graph G = newGraph(n);
	
	while( fgets(line, MAX_LEN, in) != NULL)  {
		int u=0;
		int v=0;
		
		sscanf(line, "%d %d", &u, &v);
		
		if(u==0 && v==0) {
			break;
		}
		
		addArc(G,u,v);
	
	}
	
	fprintf(out, "%s\n", "Adjacency list representation of G:");
	printGraph(out,G);
	
	List S = newList();
	for(int i=1; i<=n; i++) {
		append(S, i);
	}
	
	DFS(G,S);
	
	Graph T = transpose(G);
	
	DFS(T,S);
	
	int m=0;
	
	//printList(stdout,S);
	if(length(S) > 0) {
		moveFront(S);
		for(int i=1; i<= length(S); i++) {
			
			if( getParent(T,get(S)) == 0) {
				m++;
			}
			moveNext(S);
		}
	}
	
	fprintf(out, "%s","\n");
	
	fprintf(out, "G contains %d strongly connected components:\n", m);
	
	
	List L = newList();
	
	
	if(length(S) > 0) {
		moveBack(S);
		int z=1;
		for(int i=1; i<= length(S); i++) {
			if( getParent(T, get(S)) == 0) {
				prepend(L, get(S));
				fprintf(out, "Component %d:", z);
				printList(out, L);
				fprintf(out, "%s","\n");
				clear(L);
				z++;
			}
			else {
				prepend(L, get(S));
			}
			movePrev(S);
		}
	}
	
	fprintf(out, "%s","\n");
	
	fclose(in);
	fclose(out);
	freeList(&L);
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);
}


















