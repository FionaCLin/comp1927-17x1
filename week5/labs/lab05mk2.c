//This implements an undirected unweighted graph
//This implementation allows parallel edges

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"


typedef struct vnode * vlink;
struct vnode { 
  Vertex v; 
  vlink next; 
};

struct graph { 
//Note ints V and E are counts of vertices and edges respectively.
  int V; 
  int E; 
  vlink *adj; //an array of linked lists 
};


Edge EDGE (Vertex v, Vertex w ) {
  Edge e = {v, w};
  return e;
}

int GRAPHvalidEdge(Graph g, Edge e){
    assert(g != NULL);
    return (e.v >= 0 && e.v < g->V && 
            e.w >= 0 && e.w < g->V );
}

//Creates a new node and sets the next link
vlink NEW (Vertex v, vlink next) { 
  vlink x = malloc (sizeof *x);

  x->v = v; 
  x->next = next;
  return x;                         
}

//O(V)
Graph GRAPHinit (int V) { 
  int v;
  Graph G = malloc (sizeof *G);

  G->V = V; 
  G->E = 0;

  G->adj = malloc (V * sizeof(vlink));
  for (v = 0; v < V; v++){
    G->adj[v] = NULL;
  }
  return G;
}

void GRAPHdestroy (Graph g) {
  int i = 0;
  if (g != NULL){
     vlink cur = g->adj[i];
     vlink pre = cur;
     //First free the linked list
     while(g->adj[i] != NULL){
        if (cur == NULL) {
          free(cur);
        }
        else { 
           while(cur != NULL){
              pre = cur;
              cur = cur->next;
              free(pre);
            }
        }
        i++;
     }
     //Then free the array
     free(g->adj);
     //Then free the graph
  }
  free(g);
}

Graph GRAPHcopy(Graph g){
  if (g == NULL) {
    return NULL;
  }
  int i = 0;
  Graph g2 = GRAPHinit (g->V);
  vlink cur;
  vlink cur2;
  vlink new;
  while(g->adj[i] != NULL) {
     cur = g->adj[i];
     cur2 = g2->adj[i];
     while (cur != NULL && cur->next != NULL) {
        new = NEW (cur->v, NULL);
        new = cur;
        cur2 = new;
        cur = cur->next; //These are both wrong
        cur2 = cur2->next; // Same
     }
     cur2 = cur;
     i++;
  }
  g2->E = g->E;
  return g2;
}

int GRAPHdegree(Graph g, Vertex v) {
  //HOW TO DO IT IN A 2D ARRAY
  /*int maxNum = GRAPHnumV(g);
  int degree = 0;
  int iterate = 0;
  while (iterate < maxNum) {
    if (g->adj[iterate][v - 1] == 1){
      degree++;
    }
    iterate++;
    }
  */
  if (g == NULL) {
   printf("No edges in graph");
   return 0;
  }
  int degree = 0;
  vlink iterate = g->adj[v];
  while (iterate != NULL) {
   degree++;
   iterate = iterate->next;
  }
  return degree;
}

//Undirected graph. So each edge
//is stored twice - once from v
//and once from w
//O(1)
//This does not check for parallel edges
//To do so would make it O(n)
void GRAPHinsertE(Graph G, Edge e){ 
  if(GRAPHvalidEdge(G,e) && e.v != e.w){
     int v = e.v;
     int w = e.w;
  
     G->adj[v] = NEW (w, G->adj[v]);
     G->adj[w] = NEW (v, G->adj[w]); 
     G->E++;
  } else {
     printf("Edge not valid ignoring ");
     GRAPHEdgePrint(e);
     printf("\n");
  }
}
//Or could just add the column

int GRAPHisAdjacent(Graph g,Vertex v, Vertex w){
    vlink tmp = g->adj[v];
    int adjacent = 0;
    while(tmp != NULL && !adjacent){
        if(tmp->v == w){
            adjacent = 1;
        }
        tmp = tmp->next;
    }
    return adjacent;
}

int GRAPHadjacentVertices(Graph g, Vertex v, Vertex adj[]){
    int counter = 0;
    vlink tmp = g->adj[v];
    while(tmp != NULL){
        adj[counter] = tmp->v;
        counter++;
        tmp = tmp->next;
    }
    return counter;
}

int GRAPHedges (Edge edges[], Graph g) {
  int v, E = 0; 
  vlink t;  

  for (v = 0; v < g->V; v++) {
    for (t = g->adj[v]; t != NULL; t = t->next) {
      if (v < t->v) {
	edges[E++] = EDGE(v, t->v); 
      }
    }
  }
  return E;
}

void GRAPHEdgePrint (Edge edge) {
    printf ("%d -- %d", edge.v, edge.w);
}

int GRAPHnumV(Graph g){
    return g->V;
}

int GRAPHnumE(Graph g){
    return g->E;
}

void GRAPHshow(Graph g){
    printf("V=%d, E=%d\n", g->V, g->E); 
    int i; 
    for (i = 0; i < g->V; i++) { 
        vlink tmp = g->adj[i]; 
        while (tmp != NULL) { 
            printf("%d-%d ",i,tmp->v); 
            tmp = tmp->next; 
        } 
        if (g->adj[i] != NULL) 
            printf("\n"); 
    }
    printf("\n"); 
}