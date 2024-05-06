//CSE 310 Recitation 5 -> Dean Prach

#include <iostream>
#include <fstream>
#include <string>


using namespace std;


//Edge class which essentially represents a node class in a linked list. It will have the name of
//the destination vertex, its weight and a pointer to its next edge.
class Edge{
    public:
    string destVertex;
    int weight;
    Edge* nextVertex;

    Edge(string destVertex, int weight){
        this->destVertex = destVertex;
        this->weight = weight;
        this->nextVertex = NULL;
    }
};

//Our graph class which has an adjacency list which is an array of Edge class pointers.
//So we essentially are having an array of linked lists which will correspond to whatever
//edges each vertex has.
class Graph{
    public:
    Edge** adjList;
    int n;
    Graph(int n){
        this->n = n;
    }
    void setList(int);
    void addEdge(string, int, int);
    void printAdjList(string*);
};

//This initializes our adjacency list because we will want a list that is dynamically sized 
//based on the input value in the graph.txt file.
void Graph::setList(int n){
    this->adjList = new Edge*[n]();
    if(adjList[0] == NULL){
        
    }
}

//Inserts an edge at the corresponding vertex; it inserts at the beginning of the linked list.
void Graph::addEdge(string destVertex, int weight,int index){
    Edge* head = this->adjList[index];
    if(head == NULL){
        this->adjList[index] = (Edge*)new Edge(destVertex, weight);
        return;
    }
    Edge* temp = (Edge*)new Edge(destVertex, weight);
    temp->nextVertex = head;
    this->adjList[index] = temp;
}

//This prints out our adjacency list; if a vertex no longer has any edges it connects to,
//the list will print NULL
void Graph::printAdjList(string* vertices){
    Edge* head;
    for(int i = 0; i < this->n; ++i){
        head = this->adjList[i];
        cout<<vertices[i] << ": ";
        while(head != NULL){
            cout<< head->destVertex << "/" << head->weight << " -> ";
            head = head->nextVertex;
        }
        cout<<"NULL\n";
    }
}

//main function
int main(){
    //variables
    ifstream inFile;
    string rowInput;
    string numEdgeInput;
    string newEdge;
    string index;
    string srcVertex;
    string dstVertex;
    string inputWeight;
    int numRows;
    int numEdges;
    int weight;
    int k;

    //opening our file to read
    inFile.open("graph.txt");

    //reads the file and gets the number of vertices and the number of edges and converts them
    //to integers.
    getline(inFile,rowInput,' ');
    getline(inFile, numEdgeInput);
    numRows = stoi(rowInput);
    numEdges = stoi(numEdgeInput);
    string* indices = new string[numRows];

    //This creates an array which will contain the name of our vertices which we can later reference
    for(int i = 0; i < numRows; ++i){
        getline(inFile,index,'\n');
        indices[i] = index;
    }

    //Create and initialize our graph/adjacency list
    Graph graph = Graph(numRows);
    graph.setList(graph.n);
    

    //For each edge line in the graph.txt file we are going read each line for an edge in, then create a new
    //edge and add it to the correct spot in the adjacency list linked list
    for(int j = 0; j < numEdges; ++j){
        getline(inFile,srcVertex,' ');
        getline(inFile,dstVertex,' ');
        getline(inFile,inputWeight,'\n');
        weight = stoi(inputWeight);
        for(k = 0; k < sizeof(indices); ++k){
            if(srcVertex == indices[k]){
                break;
            }
        }
        graph.addEdge(dstVertex,weight,k);
    }
    //closing the file
    inFile.close();
    //prints out our adjacency list
    graph.printAdjList(indices);
}