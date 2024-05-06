#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <iostream>

using namespace std;

class Vertex{
    public:
    int pi;
    float key;
    int index;
    Vertex(int index, float key){
        this->index = index;
        this->key = key;
        this->pi = -1;
    }
};

//Edge class
class Edge{
    public:
    int index;
    int start;
    int end;
    float weight;
    Edge* next;
    Edge(int index, int start, int end, float weight){
        this->index = index;
        this->start = start;
        this->end = end;
        this->weight = weight;
        this->next = NULL;
    }
};

//Stack which will be used for printing out the shortest paths
class Stack{
    public:
    Vertex** stack;
    int count;
    int max_size;
    Stack(int size){
        this->stack = new Vertex*[size]();
        this->count = 0;
        this->max_size = size;
    }
    void push(Vertex*);
    Vertex* pop();
};

//MinHeap which will be used for djikstras algorithm
class MinHeap{
    public:
    Vertex** heap;
    int heap_size;
    MinHeap(int size){
        this->heap = new Vertex*[size]();
        this->heap_size = 0;
    }
    void initializeHeap(Vertex**);
    void addVertex(Vertex*);
    void heapify();
    void finishVertex();
    void printHeap();
    Vertex* pop();
    bool adjustWeight(Vertex*);
};

#endif