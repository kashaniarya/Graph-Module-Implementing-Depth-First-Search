//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){

	Graph G = newGraph(4);
	
	addArc(G,1,2);
	addArc(G,2,3);
	addArc(G,1,3);
	addEdge(G,3,4);
	
	printGraph(stdout,G);
	printf("%s", "\n");
	
	printf("%s", "\n");
	printf("%d", getSize(G));
	printf("%s", "\n");
 	printf("%d", getOrder(G));
 	printf("%s", "\n");
 	
 	
 	
	List S = newList();
    for(int i=1; i<=4; i++) append(S, i);
	
	DFS(G,S);
	
	printf("%s", "\n");
	printf("%d", getParent(G,4));
 	printf("%s", "\n");
	printf("%d", getFinish(G,1));
	printf("%s", "\n");
	printf("%d", getDiscover(G,3));
	printf("%s", "\n");
	
    Graph T=NULL, C=NULL;
    
    C = copyGraph(G);
    T = transpose(G);
   
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");
   
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   
   return(0);
	
	


}