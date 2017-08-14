# Graph-Module-Implementing-Depth-First-Search
A graph module in C using the adjacency list representation.

Arya Kashani
kashaniarya@gmail.com
UCSC ~ cmps101
pa5

Files Committed:
README 
Makefile 
List.c 
List.h
Graph.h
Graph.c 
GraphTest.c 
FindComponents.c

Brief Description of role of each file in project:
A graph module in C using the adjacency list representation.
Your graph module will, among other things, provide the capability of running DFS, 
and computing the transpose of a directed graph. DFS requires that vertices possess 
attributes for color (white, black, grey), discover time, finish time, and parent.
 To find the strong components of a digraph G call DFS(G) . As vertices are finished, place them on a stack.
 When DFS is complete the stack stores the vertices ordered by decreasing finish times. 
 Next compute the transpose GT of G. (The digraph GT is obtained by reversing the directions 
 on all edges of G.) Finally run DFS(GT ) , but in the main loop (lines 5-7) of DFS, 
 process vertices in order of decreasing finish times from the first call to DFS. 
 This is accomplished by popping vertices off the stack. When the whole process is complete, 
 the trees in the resulting DFS forest span the strong components of G. Note that the strong 
 components of G are identical to the strong components of GT .
