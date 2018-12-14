// CSCI 2530
// Assignment: 5
// Author:     Shelby Brown
// File:       mst.cpp
// Tab stops:  ***

/*Reads, from the standard input, a description of a weighted graph with integer weights, in the input format shown below. Then the program should write, on the standard output:

    the original graph G;

    the edges that are part of a minimal spanning tree T of G;

    the total weight of T.

For each graph, show the number of vertices and the number of edges. Make it clear just what each part of the output is. Don't make a reader guess what he or she is looking at. The output of your program might look like this.


Input graph:

There are 5 vertices and 6 edges

  vertices    weight
  1   2            9
  1   3           12
  2   4           18
  2   3            6
  2   5           20
  3   5           15
  
Minimal spanning tree:

There are 5 vertices and 4 edges

  vertices    weight
  2   3            6
  1   2            9
  3   5           15
  2   4           18

The total weight of the spanning tree is 48.

*/

#include "equiv.h"
#include <cstdio>
#include <cstdlib>

using namespace std;
const int maxNumEdges = 100;
typedef int (*QSORT_COMPARE_TYPE)(const void*, const void*);

//An object of type Edge represents one edge in a graph. It has three fields: two vertex numbers and a weight. Include a parameterless constructor that sets all three fields to 0. 

struct Edge
{
  int vertex1;
  int vertex2;
  int weight;
  
  Edge()
  {
     vertex1 = 0;
     vertex2 = 0;
     weight = 0;
  }

};

/* An object of type Graph represents a weighted graph. It has four fields:

    the number of vertices in the graph,
    the number of edges in the graph,
    an array of Edge structures that holds the edges,
    the physical size of that array of edges.
*/

struct Graph
{
  int verticesInGraph;
  int edgesInGraph;
  Edge* edgeHolder;
  int sizeOfHolder;

  Graph(int nv)
  {
    verticesInGraph = nv;
    edgesInGraph = 0;
    sizeOfHolder = maxNumEdges;
    edgeHolder = new Edge[sizeOfHolder];
  }
};

void insertEdge(int u, int v, int w, Graph &g);
void readGraph(Graph &g);
void writeGraph(Graph g);
int compareEdges(const Edge* A, const Edge* B);
void sortEdges(Graph g);
Graph minimalSpanningTree(Graph g);
int totalWeight(Graph k);

/*insertEdge(u,v,w,g) inserts an edge of weight w between vertices
u and v into graph g.

If there is not enough room in g to add the edge, then
insertEdge does nothing.
*/

void insertEdge(int u, int v, int w, Graph &g)
{
  if(g.edgesInGraph < maxNumEdges)
  {
    Edge* x = new Edge;
    x -> vertex1 = u;
    x -> vertex2 = v;
    x -> weight = w;
    g.edgeHolder[g.edgesInGraph] = *x;
    g.edgesInGraph = g.edgesInGraph + 1; 
  }
}

/* readGraph(Graph &g) takes and reads a description of a graph from
the standard input and returns a pointer to that graph. The graph will need
to be allocated in the heap, since it must persist after readGraph returns.
*/

void readGraph(Graph &g)
{
  int ver1,ver2, wei;
  for(int i = 0; i < maxNumEdges; i++)
  {
    scanf("%i", &ver1);
    if(ver1 != 0)
    {
      scanf("%i %i", &ver2, &wei);
      insertEdge(ver1, ver2, wei, g);
    }
    else
    {
       break;
    }
  }
}

//writeGraph(Graph g) write a description of Graph g.

void writeGraph(Graph g)
{
  printf("\n\nThere are %i vertices and %i edges", g.verticesInGraph, g.edgesInGraph);
  printf("\n\n  vertices   weight\n");
  for(int i = 0; i < g.edgesInGraph; i++)
  {
    printf("  %i   %i%12i\n",
           g.edgeHolder[i].vertex1,
           g.edgeHolder[i].vertex2,
           g.edgeHolder[i].weight);
  }
}

//compareEdges(const Edge* A, const Edge* B) takes two parameters, which will be pointers to
// particular members of the array when qsort calls it.

int compareEdges(const Edge* A, const Edge* B)
{
	return A->weight - B->weight;
}

//sortEdges(Graph g) sorts the array of edges in Graph g into ascending order by weight.

void sortEdges(Graph g)
{
	qsort((void*) g.edgeHolder, g.edgesInGraph, sizeof(Edge), (QSORT_COMPARE_TYPE) compareEdges);
} 

//minimalSpanningTree(Graph g) takes a Graph g as a parameter and returns a pointer to a minimal spanning tree of g.

Graph minimalSpanningTree(Graph g)
{
  
  int vertexes = g.verticesInGraph;
  Graph k(vertexes);
  sortEdges(g);
  ER Boss = newER(vertexes);

  int v1, v2, w;

  for(int i = 0; i < vertexes; i++)
  {
    v1 = g.edgeHolder[i].vertex1;
    v2 = g.edgeHolder[i].vertex2;
    w = g.edgeHolder[i].weight;

    if(!equivalent(Boss, v1, v2))
    {
      merge(Boss, v1, v2);
      insertEdge(v1, v2, w, k);
    }
  }


  return k;
}

//totalWeight(Graph k) computes the total weight of a graph by adding the weights of the edges.

int totalWeight(Graph k)
{
  int total = 0;
  for(int i = 0; i < k.edgesInGraph; i++)
  {
    total = total + k.edgeHolder[i].weight;
  }
  return total;
}

int main()
{
  int nv;
  scanf("%i", &nv);
  Graph g (nv);
  readGraph(g);
  printf("\nInput Graph:\n");
  writeGraph(g);
  Graph k(nv);
  k = minimalSpanningTree(g);
  printf("\nMinimal Spanning Tree:\n");
  writeGraph(k);

  int AllWeight = totalWeight(k);
  printf("\nThe total weight of the spanning tree is %i.\n", AllWeight);
  return 0;
}
