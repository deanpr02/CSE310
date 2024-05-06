#include <iostream>
#include <string>


using namespace std;


class Vertex{

    class Node{
        public:
        string edgeName;
        Node* next;
        int weight;
        Node(string edgeName, int weight){
            this->edgeName = edgeName;
            this->next = NULL;
            this->weight = weight;
        }
    };
    private:
    Node* head = NULL;
    string vertexName;
    public:
    Vertex(string vertexName){
        this->vertexName = vertexName;
    }
    string getName();
    void addEdge(string,int);
    void printEdge();
};

void Vertex::addEdge(string edgeName, int weight){
    if(this->head == NULL){
        this->head = new Node(edgeName,weight);
        return;
    }
    Node* temp = new Node(edgeName,weight);
    temp->next = this->head;
    this->head = temp;
}

void Vertex::printEdge(){
    Node* temp = this->head;
    cout<<this->vertexName << ": ";
    while(temp != NULL){
        cout << temp->edgeName << "/" << temp->weight << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

string Vertex::getName(){
    return this->vertexName;
}


class Edge{
    public:
    string destVertex;
    int weight;
    Edge* nextEdge;
    Edge(){
        nextEdge = NULL;
    }
};



class Graph{
    public:
    Edge* edges = {};
    Graph(){
    }
    int getSize();
    void initializeEdges(int);
    void addEdge(string, string, int);
    int findEdge(string edgeName);
    void setEdgeList();
    void printEdges();
};


void Graph::initializeEdges(int n){
    
    for(int i = 0; i < n; ++i){
        this->edges[i] = NULL;
    }
}

void Graph::addEdge(string edgeName, string destVertex, int weight){
    //int edgeIndex = findEdge(edgeName);
    int edgeIndex = 0;
    Edge* head = &(this->edges[edgeIndex]);
   if(head->destVertex == ""){
    head->destVertex = destVertex;
    head->weight = weight;
    return;
   }
   Edge temp = Edge();
   temp.destVertex = destVertex;
   temp.weight = weight;
   temp.nextEdge = head;
   //cout<<temp.nextEdge->destVertex;
   *head = temp;
   /*Node* temp = new Node(edgeName,weight);
    temp->next = this->head;
    this->head = temp;*/
}


void Graph::printEdges(){
    Edge* temp = &(this->edges[0]);
    while(temp != NULL){
        cout << temp->destVertex;
        temp = temp->nextEdge;
    }
}




class Test{
    public:
    int* bruh;
    int n;
    Test(int n){
        this->n = n;
    }
    void initialize();

};

void Test::initialize(){
    this->bruh = new int[this->n];
}



int main(){
    Graph test = Graph();
    test.initializeEdges(5);
    
    //cout<<test.edges[0].destVertex;
    test.addEdge("Bruh","A",100);
    test.addEdge("Bruh","B",100);
    test.addEdge("Bruh","C",100);
    //test.printEdges();

}



