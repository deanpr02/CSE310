#ifndef GRAPH_H
#define GRAPH_H
#include "datastructures.h"
#include <string>
#include <vector>
#include <limits>

//Graph class which will hold the data of our adjacency list and operate djikstras
class Graph{
    public:
    Vertex** vertices;
    Edge** adjList;
    Edge** edgeList;
    int vertCount;
    int edgeCount;
    int adjEdgeCount;
    int currVertCount;
    bool checkIfRan;
    Vertex* srcVert;
    Graph(){

    }
    Graph(int vertCount, int edgeCount){
        this->vertCount = vertCount;
        this->edgeCount = edgeCount;
        this->currVertCount = 0;
        this->vertices = new Vertex*[vertCount]();
        this->adjList = new Edge*[vertCount]();
        this->edgeList = new Edge*[edgeCount]();
        this->checkIfRan = false;
        this->adjEdgeCount = edgeCount;
    }
    void initializeLists(vector<string>); 
    bool isVertex(int);
    int findVertex(int);
    void resetVertices();
    void addDirectedEdges_F();
    void addDirectedEdges_B();
    void addUndirectedEdges_F();
    void addUndirectedEdges_B();
    void printAdjList();
    void djikstras(Vertex*);
    void djikstras_singledest(Vertex*, Vertex*);
    void printAllShortestPaths();
    void printSinglePath(Vertex*);
    void printLength(Vertex*, Vertex*);
    void testHeap();
    void test();
};

#endif