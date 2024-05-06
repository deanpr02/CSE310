#include <iostream>

using namespace std;

//Vertex class
//pi -> prev node
//index -> name of vertex essentially
//key -> weight of the vertex when using djikstras
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

//heapify method which will ensure we maintain minimum heap properties
void MinHeap::heapify(){
    int n = (this->heap_size - 2) / 2;
    int left_child;
    int right_child;
    while(n >= 0){
        int smallest = 9999;
        left_child = 2*n+1;
        right_child = 2*n+2;
        if(left_child < this->heap_size && this->heap[left_child]->key < this->heap[n]->key){
                smallest = left_child;
        }
        else{
            smallest = n;
        }
        //Check to see if right child is largest
        if(right_child < this->heap_size && this->heap[right_child]->key < this->heap[smallest]->key){
                smallest = right_child;

        }
        if(smallest != n){
            Vertex* temp = this->heap[smallest];
            this->heap[smallest] = this->heap[n];
            this->heap[n] = temp;
            n = smallest;
        }
        else{
        n--;
        }
    }
}

//Generates a heap of n size vertices
void MinHeap::initializeHeap(Vertex** vertices){
    for(int i = 0; i < this->heap_size; i++){
        this->heap[i] = vertices[i];
    }
    this->heapify();
}

//Pops minimum weighted vertex from the min heap
void MinHeap::finishVertex(){
    Vertex* temp = this->heap[this->heap_size-1];
    this->heap[0] = temp;
    this->heap_size--;
    this->heapify();
}

//Pops minimum weighted vertex from the min heap, but returns the vertex popped
Vertex* MinHeap::pop(){
    Vertex* temp = this->heap[0];
    this->heap[0] = this->heap[this->heap_size-1];
    this->heap_size--;
    this->heapify();
    return temp;
}

//prints out the heap -> used for testing
void MinHeap::printHeap(){
    cout<<"\ncount:" <<this->heap_size<<endl;
    for(int i = 0; i < this->heap_size; i++){
        cout << this->heap[i]->index << endl;
    }
    cout<<"FINISH" << endl;
}

//adds a vertex to the min heap and then heapify transforms it to meet heap properties
void MinHeap::addVertex(Vertex* vertex){
    this->heap[this->heap_size] = vertex;
    this->heap_size++;
    this->heapify();
}

//If a weight for a vertex is changed in djikstras algorithm this will modify it
bool MinHeap::adjustWeight(Vertex* src){
    for(int i = 0; i < this->heap_size; i++){
        if(src->index == this->heap[i]->index){
            if(src->key < this->heap[i]->key){
                this->heap[i]->key = src->key;
                heapify();
                return true;
            }
        }
    }
    return false;
}

//push value to the stack
void Stack::push(Vertex* vertex){
    this->stack[this->max_size - this->count - 1] = vertex;
    this->count++;
}

//pop value from the stack
Vertex* Stack::pop(){
    Vertex* ans = this->stack[this->max_size - this->count];
    this->count--;
    return ans;
}

