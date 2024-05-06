#include "datastructures.cpp"
#include <string>
#include <vector>
#include <limits>


using namespace std;
float max_flt = numeric_limits<float>::max();

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

//finds a vertex and returns the index
int Graph::findVertex(int index){
    for(int i = 0; i < this->vertCount; i++){
        if(this->vertices[i]->index == index){
            return i;
        }
    }
    return -1;
}

//resets our vertices list so if we reread a file it will update to the appropriate list
void Graph::resetVertices(){
    for(int i = 0; i < this->vertCount; i++){
        this->vertices[i]->key = max_flt;
        this->vertices[i]->pi = -1;
    }
}

//checks if the vertex exists
bool Graph::isVertex(int index){
    int count = this->currVertCount;
    for(int i = 0; i < this->currVertCount; i++){
        if(this->vertices[i]->index == index){
            return true;
        }
    }
    return false;
}

//Initalizes our vertices and edge lists
void Graph::initializeLists(vector<string> edges){
    Vertex* currVertex;
    int index;
    int start;
    int end;
    string temp;
    size_t pos;
    string delimiter = " ";
    int count;
    float weight;
    int ind;
    float max_flt = numeric_limits<float>::max();
    for(int i = 0; i < edges.size(); i++){
        count = 0;
        //We need to set up variables for index, start, end and weight
        while((pos = edges[i].find(delimiter)) != edges[i].npos){
            temp = edges[i].substr(0,pos);
            if(count == 0){
                count++;
                index = stoi(temp);
                edges[i].erase(0,pos+delimiter.length());
                continue;
            }
            if(count == 1){
                count++;
                start = stoi(temp);
                edges[i].erase(0,pos+delimiter.length());
                continue;
            }
            if(count == 2){
                count++;
                end = stoi(temp);
                edges[i].erase(0,pos+delimiter.length());
                weight = stof(edges[i]);
                break;
            }
        }
        //Generates our list of vertices
        //if(!isVertex(start)){
            //this->vertices[this->currVertCount] = new Vertex(start,max_flt);
            //this->currVertCount++;
        //}
        //Adds an edge with the new index, start, end, and weight and adds it to an array of edges.
        this->edgeList[i] = new Edge(index, start, end, weight);

}

    for(int j = 0; j < this->vertCount; j++){
        this->vertices[this->currVertCount] = new Vertex(j+1, max_flt);
        this->currVertCount++;
    }
}

//Initialize our adjacency list by adding the corresponding edges; adds to beginning of each linked list
void Graph::addDirectedEdges_F(){
    for(int k = 0; k < this->edgeCount; k++){
        int vertIndex = findVertex(this->edgeList[k]->start);
        Edge* head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = this->edgeList[k];
            continue;
        }
        Edge* temp = this->edgeList[k];
        temp->next = head;
        this->adjList[vertIndex] = temp;
    }
}

//Adds undirected edges with the 1 flag
void Graph::addUndirectedEdges_F(){
    Edge* temp;
    Edge* head;
    int test;
    int vertIndex;
    for(int k = 0; k < this->edgeCount; k++){
        vertIndex = findVertex(this->edgeList[k]->start);
        head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = this->edgeList[k];
        }
        else{
        temp = this->edgeList[k];
        temp->next = head;
        this->adjList[vertIndex] = temp;
        }


        vertIndex = findVertex(this->edgeList[k]->end);
        this->adjEdgeCount++;
        head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = new Edge(this->adjEdgeCount,this->edgeList[k]->end,this->edgeList[k]->start,this->edgeList[k]->weight);
        }
        else{
        temp = new Edge(this->adjEdgeCount,this->edgeList[k]->end,this->edgeList[k]->start,this->edgeList[k]->weight);;
        temp->next = head;
        this->adjList[vertIndex] = temp;
        }
        
    }

}

//adds undirected edges with the 2 flag 
void Graph::addUndirectedEdges_B(){
    Edge* temp;
    Edge* head;
    int test;
    int vertIndex;
    for(int k = 0; k < this->edgeCount; k++){
        vertIndex = findVertex(this->edgeList[k]->start);
        head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = this->edgeList[k];
        }
        else{
        while(head->next != NULL){
            head = head->next;
        }
        head->next = this->edgeList[k];
        }


        vertIndex = findVertex(this->edgeList[k]->end);
        this->adjEdgeCount++;
        head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = new Edge(this->adjEdgeCount,this->edgeList[k]->end,this->edgeList[k]->start,this->edgeList[k]->weight);
        }
        else{
        while(head->next != NULL){
            head = head->next;
        }
        head->next = new Edge(this->adjEdgeCount,this->edgeList[k]->end,this->edgeList[k]->start,this->edgeList[k]->weight);
        }
        
    }

}


//This will add edges to adjList for a directed graph and add edges to end of each linked list
void Graph::addDirectedEdges_B(){
    for(int k = 0; k < this->edgeCount; k++){
        int vertIndex = findVertex(this->edgeList[k]->start);
        Edge* head = this->adjList[vertIndex];
        if(head == NULL){
            this->adjList[vertIndex] = this->edgeList[k];
            continue;
        }
        while(head->next != NULL){
            head = head->next;
        }
        head->next = this->edgeList[k];
    }

}

//prints out our adjacency list
void Graph::printAdjList(){
    for(int i = 0; i < this->vertCount; i++){
        cout << "ADJ[" << this->vertices[i]->index << "]:->";
        Edge* head = this->adjList[i];
        while(head != NULL){
            cout << "[" << head->start << " " << head->end << ": " << head->weight << "]->";
            head = head->next;
        }
        cout << "NULL" << endl;
    }
}

//Single source djikstras
void Graph::djikstras(Vertex* src){
    //Checks to see if we have previously ran it so we can reset our vertices list.
    this->srcVert = src;
    if(checkIfRan){
        resetVertices();
    }
    else{
        this->checkIfRan = true;
    }
    //Initializing a priority queue of size n (vertices count)
    MinHeap queue = MinHeap(this->vertCount);
    float dist = 0;
    int currVertex;
    int tempIndex;
    Vertex* root;
    Edge* head;
    bool check;
    //Vertex* root = new Vertex(src->index, dist);

    queue.addVertex(src);
    //Update the key of src to 0
    currVertex = findVertex(src->index);
    this->vertices[currVertex]->key = dist;
    
    while(queue.heap_size > 0){
        //Root is our current vertex we are visiting
        root = queue.pop();
        //currVertex is the index of the position of the currentvertex in our vertices list
        currVertex = findVertex(root->index);
        head = this->adjList[currVertex];
        //test();
        //Search adjlist until we reach the end for that vertex
        while(head != NULL){
            //tempIndex = the vertex position of the current vertex we are 
            tempIndex = findVertex(head->end);
            if(this->vertices[tempIndex]->key == max_flt){
                this->vertices[tempIndex]->key = root->key + head->weight;
                queue.addVertex(this->vertices[tempIndex]);
                this->vertices[tempIndex]->pi = currVertex+1;
            }
            else{
                //this->vertices[tempIndex]->key = min(this->vertices[tempIndex]->key,root->key + head->weight);
                //check = queue.adjustWeight(this->vertices[tempIndex]);
                if(this->vertices[tempIndex]->key > root->key + head->weight){
                    this->vertices[tempIndex]->key = root->key + head->weight;
                    this->vertices[tempIndex]->pi = currVertex+1;
                }
                
            }
            head = head->next;
        }
    }
}


void Graph::djikstras_singledest(Vertex* src, Vertex* dest){
    this->srcVert = src;
    if(checkIfRan){
        resetVertices();
    }
    else{
        this->checkIfRan = true;
    }
    //Initializing a priority queue of size n (vertices count)
    MinHeap queue = MinHeap(this->vertCount);
    float dist = 0;
    int currVertex;
    int tempIndex;
    Vertex* root;
    Edge* head;
    bool check;
    //Vertex* root = new Vertex(src->index, dist);

    queue.addVertex(src);
    //Update the key of src to 0
    currVertex = findVertex(src->index);
    this->vertices[currVertex]->key = dist;
    
    while(queue.heap_size > 0){
        //Root is our current vertex we are visiting
        root = queue.pop();
        //currVertex is the index of the position of the currentvertex in our vertices list
        currVertex = findVertex(root->index);
        head = this->adjList[currVertex];
        
        //Search adjlist until we reach the end for that vertex
        while(head != NULL){
            //tempIndex = the vertex position of the current vertex we are 
            tempIndex = findVertex(head->end);
            if(this->vertices[tempIndex]->key == max_flt){
                this->vertices[tempIndex]->key = root->key + head->weight;
                queue.addVertex(this->vertices[tempIndex]);
                this->vertices[tempIndex]->pi = currVertex+1;
            }
            else{
                //this->vertices[tempIndex]->key = min(this->vertices[tempIndex]->key,root->key + head->weight);
                //check = queue.adjustWeight(this->vertices[tempIndex]);
                if(this->vertices[tempIndex]->key > root->key + head->weight){
                    this->vertices[tempIndex]->key = root->key + head->weight;
                    this->vertices[tempIndex]->pi = currVertex+1;
                }
                
            }
            head = head->next;
        }
        if(root->index == dest->index){
            break;
        }
    }
}

void Graph::printAllShortestPaths(){
    if(!this->checkIfRan){
        cout<< "Djikstras has not been run";
        return;
    }
    Stack stack = Stack(this->vertCount);
    for(int i = 0; i < this->vertCount; i++){
        Vertex* temp = this->vertices[i];
        cout << "The shortest path from " << this->srcVert->index << " to " << temp->index << " is:" << endl;
        stack.push(temp);
        while(temp->pi != -1){
            temp = this->vertices[findVertex(temp->pi)];
            stack.push(temp);
        }
        //stack.push(temp);
        while(stack.count > 0){
            temp = stack.pop();
            cout << "[" << temp->index << ": " << temp->key << "]->";
        }
        cout<<endl;
    }
}

void Graph::printSinglePath(Vertex* dest){
    Stack stack = Stack(this->vertCount);
    Vertex* temp = dest;
    stack.push(temp);
    while(temp->pi != -1){
        temp = this->vertices[findVertex(temp->pi)];
        stack.push(temp);
    }

    while(stack.count > 0){
        temp = stack.pop();
        cout << "[" << temp->index << ": " << temp->key << "]->";
    }
    cout<<endl;
}

void Graph::printLength(Vertex* src, Vertex* dest){
    int len = 1;
    Vertex* temp = dest;
    while(temp->pi != -1){
        temp = this->vertices[findVertex(temp->pi)];
        len++;
    }
    cout << "Length of path: " << len << endl;
    cout << "Total path distance: " << dest->key << endl;

}


void Graph::test(){
    for(int i = 0; i < this->vertCount; i++){
        cout<< "Index: " << this->vertices[i]->index << " Key: " << this->vertices[i]->key << endl;
    }
    cout<<"END\n"<<endl;
}

void Graph::testHeap(){
    cout<<this->adjList[0]->weight<<endl;;
    for(int i = 0; i < this->vertCount; i++){
        cout << "Index: " << this->vertices[i]->index << " key: " << this->vertices[i]->key << " pi: " <<  this->vertices[i]->pi << endl;
    }
}